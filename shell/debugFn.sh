#!/bin/sh
# Also work as it is with /bin/bash

# Debug variable used in the debug fn
DBG=0

# Looping over all arguments..
for arg in $@ ; do
        # .. if one starts with "DBG=", set DBG accordingly
        if [[ $arg == "DBG="* ]]; then
                # Quick parameter validation
                DBG=$(echo $arg | cut -d '=' -f 2)
                if [[ $DBG < 0 || $DBG > 1 ]]; then
                        echo Invalid DBG argument
                        echo Exit
                        exit -1
                fi
                DBG=$(echo $arg | cut -d '=' -f 2)
        fi
        # WARNING: With that approach, the last set will be activated
done

# debug function: Replacement for echo for conditional print approach
function debug() {
        if [[ $DBG != 0 ]]; then
                # Display all arguments of the function
                echo -e $@
        fi
}

# Usage examples
debug With things  separated   by    spaces
debug "\033[0;34m"Elements "\033[0m"with escape char must be entered in \"\"
debug "\033[1;32mOK\033[0m"
echo This is an echo print
debug "\033[0;31mNOK\033[0m"
debug "I can" also mix "the" parameters format 1 2 "3"

exit 0
