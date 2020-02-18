# day11

## 网络编程

### 软件架构

* `C/S`架构：全称为`Client/Server`架构，是指客户端和服务器结构；
* `B/S`架构：全称为`Browser/Server`架构，是指浏览器和服务器架构。

### 网络通信协议

> 通过计算机网络可以使多台计算机实现连接，位于同一个网络中的计算机在进行连接和通信时需要遵守一定的规则。在计算机网络中，这些连接和通信的规则被称为网络通信协议，它对数据的传输格式、传输速率、传输步骤等做了统一规定，通信双方必须同时遵守才能完成数据交换。

* `TCP/ip`协议：百度了解去，或者Google也行，不成还有必应。

### 协议分类

> 通信的协议比较复杂，`java.net`包中包含的类和接口，它们提供低层次的通信细节。我们可以直接使用这些类和接口，来专注于网络程序开发，而不需要考虑通信的细节。

* `UDP`：用户**数据报**协议`(User Datagram Protocol)`。`UDP`是**无连接通信协议**，即在数据传输时，数据的发送端和接收端不建立逻辑连接。简单来说，当一台计算机向另外一台计算机发送数据时，发送端不会确认接收端是否存在，就会发出数据，同样接收端在收到数据时，也不会向发送端反馈是否收到数据；
  * `UDP`协议消耗资源小，通信效率高，所以通常用于音频、视频和普通数据的传输，因为这种情况即使偶尔丢失一两个数据包，也不会对接受结果产生太大影响；
  * `UDP`协议传送数据时，由于`UDP`的面向无连接性，不能保证数据的完整性，因此在传输重要数据时不建议使用`UDP`协议；
  * `UDP`协议被限制在**64kb以内**，超出这个范围就不能发送了。
* `TCP`：传输控制协议`(Transmission Control Protocol)`。`TCP`协议是**面向连接**的通信协议，即传输数据之前，在发送端和接收端简历逻辑连接，然后再传输数据，它提供了两台计算机之间**可靠无差错的数据传输**。
  * `三次握手`：`TCP`协议中，在发送数据的准备阶段，客户端与服务端之间的三次交互，以保证连接的可靠；

## 网络编程三要素

> 协议、IP地址和端口号。

### 协议

> 协议：计算机网络通信必须遵守的规则。

### IP地址

> IP地址：指互联网协议地址`(Internet Protocol Address)`，俗称`IP`。`IP`地址用来给一个网络中的计算机设备做唯一的编号。

### 端口号

> 端口号是一个逻辑端口，可以看做区分同一个电脑下的不用`APP`的数据，`小于1024`的端口是保留端口，无法被普通用户使用。常见端口号：`80`端口：`http`协议、`3306`端口：`mysql`服务器、`1521`端口：`Oracle`服务器、`8080`端口：`Tomcat`服务器。

## TCP通信程序

> TCP通信能实现两台计算机之间的数据交互，通信的两端，要严格区分为**客户端`(Client)`**和**服务端`(Server)`**。
>
> 两端通信时步骤：
>
> 1. 服务端程序，需要先启动，等待客户端的连接；
> 2. 客户端主动连接服务端，连接成功才能通信，服务端不可以主动连接客户端；
> 3. 客户端请求服务端，然后客户端服务端建立逻辑连接，这个连接中包含一个`IO`对象。
> 4. 客户端和服务端则可以使用IO这个对象进行通信了，且这个`IO`对象是一个字节流对象。
>
> 在`Java`中，提供了两个类用于实现TCP通信程序：
>
> 1. 客户端`java.net.Socket`类表示。创建`Socket`对象，向服务端发出连接请求，服务端响应请求，两者建立连接开始通信；
> 2. 服务端`java.net.ServerSocket`类表示。创建`ServerSocket`对象，相当于开启一个服务，并等待客户端的连接。

## Socket类-客户端

> `Socket`类：该类实现客户端套接字，套接字指的是两台设备之间通信的端点。
>
> 1. 客户端和服务器进行交互，必须使用Socket中提供的网络流，不能使用自己创建的流对象；
> 2. 当创建客户端对象Socket的时候，就回去请求服务器和服务器经过三次握手建立连接；
>    * 如果服务器没有启动，那么就会抛出异常；
>    * 如果服务器已经启动，那么就可以进行交互了。

### 构造方法

* `Socket()`：通过系统默认类型的`SocketImpl`创建未连接套接字；
* `Socket(InetAddress address, int port)`：创建一个流套接字并将其连接到指定IP地址的指定端口号；
* `Socket(InetAddress host, int port, boolean stream)`：已过时，使用`DatagramSocket`类；
* ~~`Socket(InetAddress address, int port, InetAddress localAddr, int localPort)`~~：创建一个套接字并将其连接到指定远程地址上的指定远程端口；
* `Socket(Proxy proxy)`：创建一个未连接的套接字并指定代理类型(如果有)，该代理不管其他设置如何都应被使用；
* `Socket(String host, int port)`：创建一个套接字并将其连接到指定主机上的指定端口号；
* ~~`Socket(String host, int port, boolean stream)`~~：已过时，使用`DatagramSocket`类；
* `Socket(String host, int port, InetAddress localAddr, int localPort)`：创建一个套接字并将其连接到指定远程主机上的指定远程端口。

### 成员方法

* `OutputStream getOutputStream()`：返回此套接字的输出流；
* `InputStream getInputStream()`：返回此套接字的输入流；
* `void shutdownOutput()`：禁用此套接字的输出流；
* `void shutdownInput()`：禁用此套接字的输入流；
* `void close()`：关闭套接字。

```java
package com_01.jianmo.TCP;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class TCPClient {
	public static void main(String[] args) {
		try {
			Socket client = new Socket("127.0.0.1", 8888);

			// 写数据
			OutputStream outputStream = client.getOutputStream();
			outputStream.write("hello,服务器".getBytes());

			// 读数据
			byte[] buffer = new byte[1024];
			InputStream inputStream = client.getInputStream();
			int len = inputStream.read(buffer);
			System.out.println(new String(buffer, 0, len));

			// 释放资源
			client.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

## ServerSocket类-服务端

### 构造方法

* `ServerSocket()`：创建非绑定服务器套接字；
* `ServerSocket(int port)`：创建绑定到特定端口的服务器套接字；
* `ServerSocket(int port, int backlog)`：利用指定的`backlog`创建服务器套接字并将其绑定到指定的本地端口号；
* `ServerSocket(int port, int backlog, InetAddress bindAddr)`：使用指定的端口、侦听`backlog`和要绑定到的本地`IP`地址创建服务器。

### 成员方法

* `public Socket accept()`：获取请求的客户端对象`Socket`；

```java
package com_01.jianmo.TCP;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServer {
	public static void main(String[] args) {
		try {
			ServerSocket server = new ServerSocket(8888);
			Socket client = server.accept();

			// 读数据
			byte[] buffer = new byte[1024];
			InputStream inputStream = client.getInputStream();
			int len = inputStream.read(buffer);
			System.out.println(new String(buffer, 0, len));

			// 写数据
			OutputStream outputStream = client.getOutputStream();
			outputStream.write("hello，客户端".getBytes());

			// 先定义的后释放
			client.close();
			server.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
```

