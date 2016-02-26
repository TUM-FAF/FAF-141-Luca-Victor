## Setting up virtual machine 
- In order to connect to remote server we have to make one. For this purpose we can use virtual box. So first step is to download virtual box on our machine. Here is the [link](https://www.virtualbox.org/wiki/Downloads) to the official site. 

- After installing Virtual Box we have to download one of the linux distributors. I've chosen [this](http://www.ubuntu.com/download/server/thank-you?country=MD&version=14.04.4&architecture=amd64) one, because it's more light weighted. 

- Install ubuntu server and run the machine. It's important to change network adapter, set the amount of memory and path to iso file from which to boot the machine. So this is how it looks:
![Alt](../images/ubuntu-server.png)

## Connect via ssh
- We have to find public ip address of the ubuntu-server machine that was created. Run the following command  ```ifconfig```
- Lets first of all check if we can see the machine. Ping it using ``` ping -c 4 192.168.1.10``` You should get something like this:
![ping-machine](/images/ping.png)
- Now we can easily connect with ssh to our remote server. In linux distributors we type in ```ssh  vitiok-server@192.168.1.10```. If we are using windows we can do the same thing with [Puppy](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html). Now we can see our shell:
![Alt](../images/connect-server.png)
- Now we can perform any command from our terminal!

## Run some simple programs
- By default ubuntu has python install so we can run any python script. However in order to run any others we have install the necessary compilers. So type in the following commands to install gcc, g++:  

	```sudo apt-get install gcc```    
	```sudo apt-get install g++```

In order to install ruby we have to run a little bit more commands. I prefered to install it with rvm, but there are a lot of other ways:   

	sudo apt-get update
	sudo apt-get install build-essential make curl   
	\curl -L https://get.rvm.io | bash -s stable 
	source ~/.bash_profile   
	rvm install ruby-2.1.4

I'm a JS developer that's why I'll also install node.js:

	curl -sL https://deb.nodesource.com/setup_5.x | sudo -E bash -
	sudo apt-get install -y nodejs

- The environment is set and we are ready to go. We have to create our hello world programs:

	```touch main.c```  
	```touch main.cpp```  
	```touch index.js```  
	```touch index.rb``` 

- It's time to fill in files. We can do it using one of the CLI editors or we can do it with ```echo``` command. For example for ruby file:

	```echo "puts 'Hello World!'" >> index.rb```  

- Run programs with the following commands:

	 ```
	 gcc main.c -o main  
	 ./main  

	 g++ main.cpp -o maincpp
	 ./maincpp

	 ruby index.rb

	 node index.js
	 ```  