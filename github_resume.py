git init                     # Initialize a Git repository in the current directory
git clone <url>              # Clone a remote repository

Basic Workflow:

git status                  # Check status of changes
git add <file>              # Stage file(s) for commit
git add .                   # Stage all changes
git commit -m "message"     # Commit staged changes with message
git log                     # View commit history

Branches:

git branch                  # List branches
git branch <name>           # Create a new branch
git checkout <branch>       # Switch to a branch
git checkout -b <branch>    # Create and switch to a new branch
git merge <branch>          # Merge another branch into the current one


Remote Repositories:

git remote add origin <url>     # Connect to a remote repository
git push -u origin main         # Push for the first time
git push                        # Push local commits to remote
git pull                        # Fetch and merge remote changes



