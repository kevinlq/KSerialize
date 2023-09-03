<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/kevinlq/KSerialize">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">KSerialize</h3>

  <p align="center">
    KSerialize
    <br />
    <a href="https://github.com/kevinlq/KSerialize"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/kevinlq/KSerialize">View Demo</a>
    ·
    <a href="https://github.com/kevinlq/KSerialize/issues">Report Bug</a>
    ·
    <a href="https://github.com/kevinlq/KSerialize/issues">Request Feature</a>
  </p>
</p>

# KSerialize

[英语/English](README.md)

> `KSerialize` is a meta-object attribute in `Qt` that encapsulates the serialization and deserialization functions for basic data types. This makes it convenient for daily development and use. The project refers to the `QtJsonSerializer` project, allowing it to be easily used in older versions of `Qt`.


## 使用指南

### 安装

You can install KSerialize using the following command:

```C++
git clone https://github.com/kevinlq/KSerialize.git
cd KSerialize
mkdir build && cd build
cmake ..
make
sudo make install
```

### 使用

在你的C++代码中，包含KSerialize头文件
```C++
#include "KSerialize.h"

```

- 简单对象序列化

```C++
    DStudent st;
    st.setName(QStringLiteral("法外狂徒张三"));
    st.setNumber("123456789");
    st.setSex(QStringLiteral("男"));
    st.setBirthda(QDateTime::currentDateTime());
	
	KSerialize serial;
	auto json = serial.serialize(score);
	qDebug() << json;
```

    
## 文档与贡献

更多关于KSerialize的信息和用法，请查看README.md文件。如果你有任何问题或建议，欢迎提交issue或pull request。同时，我们也欢迎你为KSerialize做出贡献！

查看更多关于这个项目的贡献者，请阅读 [contributors](#)


## 致谢

感谢 [QtJsonSerializer](#) 开源项目


## 版本历史

* V 0.0.1 完成基本数据结构的序列化开发


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/kevinlq/KSerialize.svg?style=for-the-badge
[contributors-url]: https://github.com/kevinlq/KSerialize/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/kevinlq/KSerialize.svg?style=for-the-badge
[forks-url]: https://github.com/kevinlq/KSerialize/network/members
[stars-shield]: https://img.shields.io/github/stars/kevinlq/KSerialize.svg?style=for-the-badge
[stars-url]: https://github.com/kevinlq/KSerialize/stargazers
[issues-shield]: https://img.shields.io/github/issues/kevinlq/KSerialize.svg?style=for-the-badge
[issues-url]: https://github.com/kevinlq/KSerialize/issues
[license-shield]: https://img.shields.io/github/license/kevinlq/KSerialize.svg?style=for-the-badge
[license-url]: https://github.com/kevinlq/KSerialize/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/kevinlq
[QtJsonSerializer-url]: https://github.com/Skycoder42/QtJsonSerializer

