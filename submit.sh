# check if reprozip is installed

if ! command -v reprozip &> /dev/null
then
    echo "reprozip could not be found"
    echo "check how to install reprozip:"
    echo "https://docs.reprozip.org/en/latest/install.html"
    exit
fi


# if .reprozip-trace exists, then remove it

if [ -f .reprozip-trace ]; then
    rm .reprozip-trace
fi

# Run reprozip trace

reprozip trace bash ./run.sh

# if submission.rpz exists, then remove it

if [ -f submission.rpz ]; then
    rm submission.rpz
fi

# Run reprozip pack

reprozip pack submission.rpz