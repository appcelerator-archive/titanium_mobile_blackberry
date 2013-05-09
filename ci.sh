# Auto fetch and package command
# $ curl -L https://raw.github.com/appcelerator/titanium_mobile_blackberry/master/ci.sh | sh

# Fetch Titanium BlackBerry Sdk


if [[ 'git remote -v | tail -1' =~ .*titanium_mobile_blackberry.* ]]
then
     git clone --recursive https://github.com/appcelerator/titanium_mobile_blackberry

    # Enter repo root directory
    cd titanium_mobile_blackberry
fi

./create_sdk

cd build/sdk