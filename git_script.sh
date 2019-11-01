

MSG=$1
BRANCH=$2

git add -A

git commit -am "$MSG"

git rebase -i develop

git push -f origin $BRANCH
