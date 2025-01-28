import os
import re
import datetime
import subprocess

# Set relative path for version.h inside the project
PROJECT_DIR = os.path.dirname(os.path.abspath(__file__))  # Get the current folder where the script is running
VERSION_FILE = os.path.join(PROJECT_DIR, "version.h")  # Relative path to version.h inside the project

# Function to read the current version from version.h
def read_version():
    if not os.path.exists(VERSION_FILE):
        print(f"Error: {VERSION_FILE} not found! Creating a new one.")
        with open(VERSION_FILE, "w") as file:
            file.write('#ifndef VERSION_H\n#define VERSION_H\n#define PROJECT_VERSION "1.0"\n#define BUILD_DATE "Undefined"\n#define BUILD_TIME __TIME__\n#endif')
        return "1.0"

    with open(VERSION_FILE, "r") as file:
        content = file.read()
        match = re.search(r'#define PROJECT_VERSION "(.*?)"', content)
        return match.group(1) if match else "1.0"

# Function to update the version and release date
def update_version():
    current_version = read_version()
    major, minor = map(int, current_version.split("."))

    new_version = f"{major}.{minor + 1}"

    # Get current date in format YYYY-MM-DD
    release_date = datetime.datetime.now().strftime("%Y-%m-%d")

    # Open version.h and read its content
    with open(VERSION_FILE, "r") as file:
        content = file.read()

    # Replace PROJECT_VERSION and BUILD_DATE
    new_content = re.sub(r'#define PROJECT_VERSION ".*?"', f'#define PROJECT_VERSION "{new_version}"', content)
    new_content = re.sub(r'#define BUILD_DATE ".*?"', f'#define BUILD_DATE "{release_date}"', new_content)

    # Write the updated content back to version.h
    with open(VERSION_FILE, "w") as file:
        file.write(new_content)

    print(f"Updated version: {current_version} → {new_version}, Release Date: {release_date}")
    return new_version, release_date

# Function to commit and push to Git
def git_commit_and_push(version, release_date):
    commit_message = f"Auto-update: Version {version} - Release Date {release_date}"

    subprocess.run(["git", "add", VERSION_FILE])
    subprocess.run(["git", "commit", "-m", commit_message])
    subprocess.run(["git", "push"])

    print(f"Committed and pushed: {commit_message}")

# Run the script
if __name__ == "__main__":
    new_version, release_date = update_version()
    git_commit_and_push(new_version, release_date)
