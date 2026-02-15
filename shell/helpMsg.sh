#!/bin/sh
# Also work as it is with /bin/bash

help() {
        echo "$(basename $0)"
        echo "Here, you can give a full explanation of the usage and " \
             "its parameters"
        echo "usage: ./$(basename $1) [-h|--help] <param1> <param2> ..."
        echo "       -h,--help : Display help message"
        echo "       param1    : Do this"
        echo "       param2    : Do that"
}

help_simplified() {
        echo "$(basename $0)"
        echo "Or you can set 2 different fns. " \
             "For example, a simplified version."
        echo "usage: ./$(basename $1) [-h|--help] <param1> <param2> ..."
}

for arg in $@; do
        # It is your choice to do one or the other approach
        #if [[ $arg == "-h" || $arg == "--help" ]]; then
        if [[ $arg == "--help" ]]; then
                help $0
                exit 1
        elif [[ $arg == "-h" ]]; then
                help_simplified $0
                exit 1
        fi
done

exit 0
