FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
WORKDIR /home/root
VOLUME /home/root

RUN apt update && \
	apt-get install -y lsb-release valgrind clang wget nano python3 python3-pip build-essential && \
	pip install norminette==3.3.50 && \
	apt-get install -y cmake git curl python3.8-venv && \
	apt-get install -y libreadline-dev 


RUN apt update && \
	wget https://raw.github.com/xicodomingues/francinette/master/bin/install.sh && chmod +x install.sh && ./install.sh
	
RUN wget https://github.com/Peltoche/lsd/releases/download/0.23.1/lsd-musl_0.23.1_amd64.deb && \
	dpkg -i lsd-musl_0.23.1_amd64.deb && \
	echo "alias ls='lsd'">> ~/.bashrc

ENV HOME /home/pool
CMD ["bash"]
