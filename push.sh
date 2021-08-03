#!/bin/bash


echo
echo "Add commit message: "
echo

read msg

git add -A
git commit -m "$msg"
git push 
