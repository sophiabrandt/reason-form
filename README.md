<!-- PROJECT SHIELDS -->

[![Contributors][contributors-shield]][contributors-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/sophiabrandt/reason-form">
    <img src="logo.png" alt="Logo">
  </a>

  <h3 align="center">Reason Form</h3>

  <p align="center">
    Build a React form with ReasonReact
    <br />
    <a href="https://github.com/sophiabrandt/reason-form"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://reason-form.firebaseapp.com">View Demo</a>
    ·
    <a href="https://github.com/sophiabrandt/reason-form/issues">Report Bug</a>
    ·
    <a href="https://github.com/sophiabrandt/reason-form/issues">Request Feature</a>
  </p>
</p>

<!-- TABLE OF CONTENTS -->

## Table of Contents

- [About the Project](#about-the-project)
  - [Built With](#built-with)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)
- [Acknowledgements](#acknowledgements)

<!-- ABOUT THE PROJECT -->

## About The Project

**UPDATE**:
ReasonML + BuckleScript is now [Rescript](https://rescript-lang.org/blog/bucklescript-is-rebranding).
As the ecosystem has changed around those tools, this repository is **out of date**.

---
> Build a form with ReasonReact and React hooks

The project demonstrates how to create a form with form validation and custom hooks in ReasonML.

**☞ [View Demo](https://reason-form.firebaseapp.com)**.

Try to submit a form. A successful submit logs to the JavaScript console (there is no back-end logic implemented).

This repository follows my process of learning ReasonReact:

- [Learning ReasonReact Step by Step Part: 0](https://dev.to/sophiabrandt/learning-reasonreact-step-by-step-part-0-48la)
- [Learning ReasonReact Step by Step Part: 1](https://dev.to/sophiabrandt/learning-reasonreact-step-by-step-part-1-15ih)
- [Learning ReasonReact Step by Step Part: 2](https://dev.to/sophiabrandt/learning-reasonreact-step-by-step-part-2-3h20)
- [Learning ReasonReact Step by Step Part: 3](https://dev.to/sophiabrandt/learning-reasonreact-step-by-step-part-3-2010)
- [Learning ReasonReact Step by Step Part: 4](https://dev.to/sophiabrandt/learning-reasonreact-step-by-step-part-4-114h)
- [Learning ReasonReact Step by Step Part: 5](https://dev.to/sophiabrandt/learning-reasonreact-step-by-step-part-5-m6l)
- [Learning ReasonReact Step by Step Part: 6](https://dev.to/sophiabrandt/learning-reasonreact-step-by-step-part-6-2mim)
- [Learning ReasonReact Step by Step Part: 7](https://dev.to/sophiabrandt/learning-reasonreact-step-by-step-part-7-12fg)
- [Learning ReasonReact Step by Step Part: 8](https://dev.to/sophiabrandt/learning-reasonreact-step-by-step-part-8-5f75)
- [Learning ReasonReact Step by Step Part: 9](https://dev.to/sophiabrandt/learning-reasonreact-step-by-step-part-9-4089)
- [Learning ReasonReact Step by Step Part: 10](https://dev.to/sophiabrandt/learning-reasonreact-step-by-step-part-10-2mpn)

### Built With

- [ReasonML](https://reasonml.github.io/)
- [ReasonReact](https://reasonml.github.io/reason-react/)
- [Bulma](https://bulma.io)

<!-- GETTING STARTED -->

## Getting Started

To get a local copy up and running follow these steps:

### Prerequisites

You need npm or yarn.

- npm

```sh
npm install npm@latest -g
```

- yarn

```sh
npm install yarn -g
```

Install [Bucklescript and Reason](https://reasonml.github.io/docs/en/installation):

```sh
npm install -g bs-platform --unsafe-perm # or yarn global add bs-platform --unsafe-perm
```

### Installation

1. Clone the repo

```sh
git clone https://github.com/sophiabrandt/reason-form.git
```

3. Install NPM packages

```sh
cd reason-form && yarn install
```

4. Checkout commit

If you want to see the basic form without validation:

```sh
git fetch && git fetch --tags
git checkout finished-basic-form-with-dev-routing
```

Otherwise just use the master branch.

<!-- USAGE EXAMPLES -->

## Usage

Run the project locally under `http://localhost:3000` via:

```sh
npm run start
```

Create a production build:

```sh
npm run build
```

<!-- ROADMAP -->

## Roadmap

See the [open issues](https://github.com/sophiabrandt/reason-form/issues) for a list of proposed features (and known issues).

<!-- CONTRIBUTING -->

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->

## License

Distributed under the MIT License. See `LICENSE` for more information.

<!-- CONTACT -->

## Contact

Sophia Brandt - [@hisophiabrandt](https://twitter.com/hisophiabrandt)

Project Link: [https://github.com/sophiabrandt/reason-form](https://github.com/sophiabrandt/reason-form)

<!-- ACKNOWLEDGEMENTS -->

## Acknowledgements

- [Img Shields](https://shields.io)
- [Choose an Open Source License](https://choosealicense.com)
- [Best-README-Template](https://github.com/othneildrew/Best-README-Template/blob/master/README.md)
- [Using Custom React Hooks to Simplify Forms](https://upmostly.com/tutorials/using-custom-react-hooks-simplify-forms)

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/sophiabrandt/reason-form.svg?style=flat-square
[contributors-url]: https://github.com/sophiabrandt/reason-form/graphs/contributors
[issues-shield]: https://img.shields.io/github/issues/sophiabrandt/reason-form.svg?style=flat-square
[issues-url]: https://github.com/sophiabrandt/reason-form/issues
[license-shield]: https://img.shields.io/github/license/sophiabrandt/reason-form.svg?style=flat-square
[license-url]: https://github.com/sophiabrandt/reason-form/blob/master/LICENSE.txt
