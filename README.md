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

[中文/Chinese](README_zh.md)

> `KSerialize` is a meta-object attribute in `Qt` that encapsulates the serialization and deserialization functions for basic data types. This makes it convenient for daily development and use. The project refers to the `QtJsonSerializer` project, allowing it to be easily used in older versions of `Qt`.


## build and run

### Installation

You can install KSerialize by following these commands:

```C++
git clone https://github.com/kevinlq/KSerialize.git
cd KSerialize
mkdir build && cd build
cmake ..
make
sudo make install
```

### Using

In your C++ code, include the KSerialize header file.

```C++
#include "KSerialize.h"

```

- Simple Object Serialization

```C++
    DStudent st;
    st.setName(QStringLiteral("zhang san"));
    st.setNumber("123456789");
    st.setSex(QStringLiteral("x"));
    st.setBirthda(QDateTime::currentDateTime());
	
	KSerialize serial;
	auto json = serial.serialize(score);
	qDebug() << json;
```

## Documentation and Contributions

For more information about KSerialize and how to use it, please refer to the README.md file. If you have any questions or suggestions, feel free to submit issues or pull requests. We also welcome you to contribute to KSerialize!

Please read [CONTRIBUTING.md](#) for details on our code of conduct, and the process for submitting pull requests to us.

## Acknowledgments

Thank [QtJsonSerializer](#) for the open-source project.

## Release History

* V 0.0.1 Complete common http request encapsulation



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

