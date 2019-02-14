# kali linux暴力破解WiFi

## 参考地址

>   优：https://www.cnblogs.com/york-hust/archive/2012/07/07/2580340.html
>
>   https://blog.csdn.net/Edroid1530/article/details/74446651?locationNum=4&fps=1

## 要点说明

>   需要管理员权限执行以下命令

## 本地字典

>   路径`/usr/share/wordlists/rockyou.txt.gz`
>
>   解压：`gzip -d /usr/share/wordlists/rockyou.txt.gz`
>
>   `kali linux`在树莓派上的字典在`/usr/share/wfuzz/wordlist/`目录中
>
>   使用组合命令可以查询，使用管理员执行：`find * / | grep wordlists | less`

## 暴力破解

*   检查网卡是否支持监听模式

    >   `airmon-ng`，有输出则表示支持，没输出即为不支持

*   开启无线网卡的监听模式

    >   `airmon-ng start wlan0`，`wlan0`为无线网卡名，开启后使用`ifconfig`查看无线网卡名由`wlan0`已经变成了`wlan0mon`

*   搜索附近的WIFI网络

    >   `airodump-ng wlan0mon`，使用`Ctrl + c`终止搜索。可以得到如下信息

| BSSID | CH   | ENC  | ESSID  | PWR  |
| ----- | ---- | ---- | ------ | ---- |
| MAC地址 | 信道   | 加密方式 | wifi名称 | 信号强度 |

*   抓取握手包

    >   `airodump-ng -c 10 --bssid FF:FF:FF:FF:FF:FF:FF -w ~/ wlan0mon`
    >
    >   *   `-c`：指定信道
    >   *   `--bssid`：指定bssid号，BSS：`Basic Service Set`
    >   *   `-w`：指定抓取的数据包的保存位置

*   攻击连接的设备

    >   攻击已经链接的设备迫使其掉线，重新链接进行抓取密码数据包。
    >
    >   `aireplay-ng -0 2 -a FF:FF:FF:FF:FF:FF:FF -c FF:FF:FF:FF:FF:FF:FF wlan0mon`
    >
    >   `-0`：后面指定攻击次数，`-0`表示`deauth`攻击模式。
    >
    >   `-a`：指定攻击的AP的MAC地址
    >
    >   `-c`：指定客户端的MAC地址。

*   重要提示

    >    攻击成功后，抓取数据包的终端第一行会显示抓到的数据包，否则攻击不成功。攻击不成功的原因有多种，攻击不成功的原因有多种。参考第二个链接原因

*   开始破解

    >   `aircrack-ng -w dic 捕获的cap文件`
    >
    >   `-w`：指定字典
    >
    >   最后是抓到的数据包

## 扫尾工作

>   `airmon-ng stop wlan0mon`用来关闭网卡的监听模式。
