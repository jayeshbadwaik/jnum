#!/bin/bash

find . -type d -name ".git" -prune -o -type d -name *jnum*  -print | sed -e "p;s/jnum/$1/" | xargs -n2 mv
find . -type d -name ".git" -prune -o -type f -name *jnum*  -print | sed -e "p;s/jnum/$1/" | xargs -n2 mv
find . -type d -name ".git" -prune -o -type f -exec sed -i "s/jnum/$1/g" {} \;
find . -type d -name ".git" -prune -o -type f -exec sed -i "s/JNUM/$2/g" {} \;




