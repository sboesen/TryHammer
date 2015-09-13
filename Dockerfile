FROM ubuntu:latest
MAINTAINER cloudaku <devops@hostname.io>

RUN apt-get update
RUN apt-get install build-essential git curl python python-pip python-dev exuberant-ctags pkg-config libglib2.0-dev -y
RUN curl -sL https://deb.nodesource.com/setup | bash -
RUN apt-get install nodejs at -y

# Install codebox
ENV USER root
RUN npm install -g node-gyp
RUN npm install codebox
RUN cd /node_modules/codebox/node_modules/shux/node_modules/pty.js && make clean && make


# Install hammer
RUN pip install --upgrade pip 
RUN pip install scons
RUN git clone https://github.com/UpstandingHackers/hammer.git /hammer
RUN cd /hammer && PYTHONPATH=/usr/local/lib/python2.7/dist-packages/scons-2.3.6 scons install

RUN ldconfig


# Add init script
ADD init.sh /init.sh
ADD hammer_examples /hammer_examples
ADD commands.json /node_modules/codebox/core/cb.run.file/commands.json
ADD addon-built.js /node_modules/codebox/addons/cb.help/addon-built.js

EXPOSE 8000
ENTRYPOINT ["bash", "/init.sh"]
CMD ["run"]
