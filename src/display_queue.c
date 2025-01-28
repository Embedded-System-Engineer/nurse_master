#include "../inc/appRes.h"

typedef struct {
    Node* node_head; // Head of the urgent state queue
    Node* node_current;
    Node* newNode;
    Node* acceptNode;
    uint8_t max_node;
    uint8_t node_state;
    uint8_t accept_state;

} st_state_type_t;

static  st_state_type_t gstCallNode;
static  st_state_type_t gstUrgentNode;
static  uint8_t clear_all_display;

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
static Node * insert_node(QueueItem item) {
    if (item.State == URGENT_STATE) { // Urgent state
        if (gstUrgentNode.max_node >= MAX_DEVICE_USED) {
            // Reset queue if max nodes reached (wrap around)
            gstUrgentNode.max_node = 0;
            Node* temp = gstUrgentNode.node_head;
            while (temp) {
                Node* next = temp->next;
                free(temp);
                temp = next;
            }
            gstUrgentNode.node_head = NULL;
        }

        // Check if the node with the same address already exists
        Node* temp = gstUrgentNode.node_head;
        while (temp != NULL) {
            if (temp->item.address == item.address) {
                return (NULL); // Node with this address already exists, do not insert
            }
            temp = temp->next;
        }

        // Create new node
        Node* new_node = (Node*) malloc(sizeof (Node));
        if (!new_node) {
            return (0); // Allocation failed
        }
        new_node->item.address = item.address;
        new_node->item.swId = item.swId;
        new_node->item.RId = item.RId;
        new_node->item.State = item.State;
        new_node->item.timestamp = item.timestamp;
        new_node->next = NULL;

        // Insert node in the correct position based on timestamp (oldest first)
        if (gstUrgentNode.node_head == NULL || gstUrgentNode.node_head->item.timestamp > new_node->item.timestamp) {
            new_node->next = gstUrgentNode.node_head;
            gstUrgentNode.node_head = new_node;
        } else {
            Node* current = gstUrgentNode.node_head;
            while (current->next != NULL && current->next->item.timestamp <= new_node->item.timestamp) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }

        gstUrgentNode.max_node++;
        return new_node;
    }

    if (item.State == CALL_STATE) { // Call state
        if (gstCallNode.max_node >= MAX_DEVICE_USED) {
            // Reset queue if max nodes reached (wrap around)
            gstCallNode.max_node = 0;
            Node* temp = gstCallNode.node_head;
            while (temp) {
                Node* next = temp->next;
                free(temp);
                temp = next;
            }
            gstCallNode.node_head = NULL;
        }

        // Check if the node with the same address already exists
        Node* temp = gstCallNode.node_head;
        while (temp != NULL) {
            if (temp->item.address == item.address) {
                return (NULL); // Node with this address already exists, do not insert
            }
            temp = temp->next;
        }

        // Create new node
        Node* new_node = (Node*) malloc(sizeof (Node));
        if (!new_node) {
            return (NULL); // Allocation failed
        }
        new_node->item.address = item.address;
        new_node->item.swId = item.swId;
        new_node->item.RId = item.RId;
        new_node->item.State = item.State;
        new_node->item.timestamp = item.timestamp;
        new_node->next = NULL;

        // Insert node in the correct position based on timestamp (oldest first)
        if (gstCallNode.node_head == NULL || gstCallNode.node_head->item.timestamp > new_node->item.timestamp) {
            new_node->next = gstCallNode.node_head;
            gstCallNode.node_head = new_node;
        } else {
            Node* current = gstCallNode.node_head;
            while (current->next != NULL && current->next->item.timestamp <= new_node->item.timestamp) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }

        gstCallNode.max_node++;
        return new_node;
    }
    return (NULL);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
static void remove_node(uint8_t address) {
    Node* temp = gstUrgentNode.node_head;
    Node* prev = NULL;

    // Remove from urgent queue
    while (temp != NULL && temp->item.address != address) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL) {
        if (prev == NULL) {
            gstUrgentNode.node_head = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
        gstUrgentNode.max_node--;
        return;
    }

    // Remove from call queue if not found in urgent queue
    temp = gstCallNode.node_head;
    prev = NULL;

    while (temp != NULL && temp->item.address != address) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL) {
        if (prev == NULL) {
            gstCallNode.node_head = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
        gstCallNode.max_node--;
    }
}

static void getNextItem( st_state_type_t *type) {
    ATOMIC_BEGIN
    type->node_current = type->node_current->next;
    ATOMIC_END
    if (type->node_current == NULL) {
        ATOMIC_BEGIN
        type->node_current = type->node_head; // reset queue
        type->newNode = type->node_head;
        type->node_state = 1;
        ATOMIC_END
        return;
    }
    type->node_state = 2;
}

static void CancelState(uint8_t address) {
    remove_node(address);
    if (gstCallNode.max_node == 0 && gstUrgentNode.max_node == 0) {
        //clear display
        clear_all_display = 1;
        RegisterOnUserSystemState(CANCEL_STATE);
        return;
    }
    if (gstUrgentNode.max_node > 0 && gstUrgentNode.node_current->item.address == address) {
        //remove from queue
        //Go to Remove From Queue
        getNextItem(&gstUrgentNode);
        return;
    }
    if (gstCallNode.max_node > 0 && gstCallNode.node_current->item.address == address) {
        getNextItem(&gstCallNode);
        return;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                   |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
void putIntoQueue(QueueItem receivedData) {
    if (systemInactive() == false) {
        return;
    }
    if (receivedData.State == CANCEL_STATE) {
        CancelState(receivedData.address);
        return;
    }
    Node * newNode = insert_node(receivedData);
    if (newNode == NULL) {
        return;
    }

    if (receivedData.State == URGENT_STATE) {
        //new request for urgent
        setActiveBuzzer();
        gstUrgentNode.newNode = newNode;
        gstUrgentNode.node_current = newNode;
        gstUrgentNode.node_state = 1;

        return;
    }

    if (receivedData.State == CALL_STATE) {
        setActiveBuzzer();
        gstCallNode.newNode = newNode;
        gstCallNode.node_current = newNode;
        gstCallNode.node_state = 1;
        return;
    }

}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <getPeriodIsDone>                                                    |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void getPeriodIsDone                                                        |
 | < @Description         : one Period is done or not                                                   |      
 | < @return              : void                                                                        |          
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t userAccptIP(uint8_t ip) {
    static uint8_t acceptState = 0;
    CallPointOptions_t optionByte;
    static uint8_t GeneralState;
    memAddresst_t address;
    switch (acceptState) {
        case 0:
            address = MEMORY_START_SWITCH_CONFIG + (ip - 1) * sizeof (stCallPointConfig_t) + 4; // load config
            if (LoadFromMemory(address, (uint8_t *) & optionByte, 1)) {
                if (optionByte.DisapledSystem) {
                    GeneralState = SYSTEM_CANCEL_EVENT;
                    acceptState = 1;
                } else {
                    GeneralState = SYSTEM_ACCEPT_EVENT;
                    acceptState = 2;
                }

            }
            break;
        case 1:
            address = MEMORY_START_SWITCH_DATA + (ip - 1) * sizeof (stCallPointData_t) + 4; // load config
            if (SaveIntoMemory(address, (uint8_t *) & GeneralState, 1)) {
                QueueItem item;
                item.address = ip;
                item.State = CANCEL_STATE;
                ATOMIC_BEGIN
                putIntoQueue(item);
                ATOMIC_END
                acceptState = 2;
            }

            break;
        case 2://accept point request
            if (AcceptPointRequest(ip)) {
                acceptState = 0;
                GeneralState = 0;
                return (1);
            }
            break;
    }
    return (0);
}

static void QueueProcess( st_state_type_t *type) {

    switch (type->node_state) {
        case 0: //init state
            type->node_current = type->node_head;
            type->node_state = 2;
            break;
        case 1://new Request
            if (updateDisplayRequest(&type->newNode->item, 1)) {
                type->node_state = 3;
                setCurrentItem(type->newNode->item);
                RegisterOnUserSystemState(type->newNode->item.State);
            }
            break;

        case 2://Go to Next In display Queue
            if (updateDisplayRequest(&type->node_current->item, 0)) {
                setCurrentItem(type->node_current->item);
                RegisterOnUserSystemState(type->node_current->item.State);
                type->node_state = 3;
            }
            break;
        case 3:
            if (getPeriodIsDone()) {
                getNextItem(type);
            }
            break;
        default:
            type->node_state = 0;
            break;
    }
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
void processQueue() {



    if (gstUrgentNode.max_node > 0) {
        QueueProcess(&gstUrgentNode);
        return;
    }

    if (gstCallNode.max_node > 0) {
        QueueProcess(&gstCallNode);
        return;
    }

    if (clear_all_display) {
        if (ClearDisplay()) {
            RegisterOnUserSystemState(CANCEL_STATE);
            clear_all_display = 0;
        }
    }




}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t acceptCurrentPoint(uint8_t ip,  st_state_type_t *type) {
    //point is exits
    // Check if the node with the same address already exists
    if (type->accept_state == 0) {
        Node* temp = type->node_head;
        while (temp != NULL) {
            if (temp->item.address == ip) {
                type->accept_state = 1;
                return (0);
            }
            temp = temp->next;
        }
        //point not fount
        return (1);
    }

    if (userAccptIP(ip)) {
        type->accept_state = 0;
        return (1);
    }
    return (0);

}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
static uint8_t acceptAllSystem( st_state_type_t *type) {

    switch (type->accept_state) {
        case 0:
            if (type->max_node > 0) {
                type->acceptNode = type->node_head;
                type->accept_state = 2;
                return (0);
            }
            return (1);
            break;
        case 2:
            if (userAccptIP(type->acceptNode->item.address)) {
                type->acceptNode = type->acceptNode->next;
                if (type->acceptNode == NULL) {
                    type->accept_state = 0;
                    return (1);
                }
            }
            break;
        default:
            break;
    }
    return (0);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
uint8_t acceptAllCallState() {
    return acceptAllSystem(&gstCallNode);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
uint8_t acceptAllUregntState() {
    return acceptAllSystem(&gstUrgentNode);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
uint8_t acceptCurrentUrgentPoint(uint8_t ip) {
    return acceptCurrentPoint(ip, &gstUrgentNode);
}

/*
 --------------------------------------------------------------------------------------------------------
 |                                 <QueuSetCallPoint>                                                     |
 --------------------------------------------------------------------------------------------------------
 | < @Function            : void QueuSetCallPoint                                                       |
 | < @Description         : set data of the system                                                      | 
 | < @return              : void                                                                        |                   
 --------------------------------------------------------------------------------------------------------
 */
uint8_t acceptCurrentCallPoint(uint8_t ip) {
    return acceptCurrentPoint(ip, &gstCallNode);
}


