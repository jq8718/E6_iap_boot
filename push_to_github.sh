#!/bin/bash
# ============================================================
# Push E6 IAP Bootloader project to GitHub via SSH
# Run this script in Git Bash at project root
# ============================================================

set -e

PROJECT_DIR="D:/XC/E6/E6LD 1.1/bootload/iap_boot"
REPO_URL="git@github.com:jq8718/E6_iap_boot.git"

cd "$PROJECT_DIR"

echo "[1/5] Initializing git repository..."
if [ ! -d .git ]; then
    git init
fi

echo "[2/5] Configuring .gitignore..."
if [ ! -f .gitignore ]; then
    cat > .gitignore <<'EOF'
# Build outputs
EWARM/Debug/
EWARM/Release/
EWARM/settings/
EWARM/*.dep
EWARM/*.ewt
EWARM/*.ewd
EWARM/*.ewp.bak

MDK/Objects/
MDK/Listings/
MDK/*.uvguix.*
MDK/*.uvoptx
MDK/*.scvd

# IAR / Keil generated
*.o
*.obj
*.lst
*.map
*.elf
*.bin
*.hex
*.axf
*.srec

# IDE
.vscode/
*.code-workspace

# OS
Thumbs.db
.DS_Store
EOF
fi

echo "[3/5] Adding files and committing..."
git add .
git commit -m "Initial commit: I2C IAP Bootloader baseline" || true

echo "[4/5] Adding SSH remote..."
git remote remove origin 2>/dev/null || true
git remote add origin "$REPO_URL"
git branch -M main

echo "[5/5] Pushing to GitHub..."
git push -u origin main

echo "Done. Repository pushed to $REPO_URL"

# Note: A post-commit hook has been installed at .git/hooks/post-commit
# so future commits in this repository are automatically pushed to origin.
