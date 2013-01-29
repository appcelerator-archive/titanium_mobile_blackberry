# Auto fetch and package command
# $ curl -L https://raw.github.com/appcelerator/titanium_mobile_blackberry/master/ci.sh | sh

# Fetch Titanium BlackBerry Sdk
git clone --recursive https://github.com/appcelerator/titanium_mobile_blackberry

# Enter repo root directory
cd titanium_mobile_blackberry

# Determine the current git commit hash
GIT_VERSION=$(/usr/bin/git log -1 --format="%H")

# Create Time Stamp
DATE=$(date +"%Y%m%d%H%M")

# Check OS
OS=$(uname -s)

BB_PATH="/Applications"

# Set bbndk path
if [ "$OS" == 'Linux' ]; then
    BB_PATH="/opt"
fi

# Set source for build
source $BB_PATH/bbndk/bbndk-env.sh

# Build v8 runtime
cd runtime && make

# Move to sdk build file directory
cd ../cli/commands

# Create temp package.json to install wrench dep
echo "{\"name\":\"tmp\",\"version\":\"0.0.1\"}" > package.json

# Install node.js wrench module
npm install wrench && rm package.json

# Build sdk and Move to build output directory
./create_sdk && cd ../../build/sdk

# Package SDK
tar -zcvf blackberry_$DATE.tar.gz blackberry