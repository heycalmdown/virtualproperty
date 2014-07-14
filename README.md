
# virtualproperty

  [![build status][travis-image]][travis-url]

  Make your simple object to get power of virtual getter or setter like Python do with __set__ __get__.

## Installation

```
$ npm install virtualproperty
```

## Example

```js
var virtualproperty = require('virtualproperty');
var a = virtualproperty.expose();
a.prototype.__get__ = function (key) {
  return 'a';
};

assert(a.a === 'a');
assert(a.b === 'a');
```

## Running tests

  Install dev deps

    $ npm install -d

  Run the tests

    $ npm test

## License

  MIT

[travis-image]: https://img.shields.io/travis/heycalmdown/virtualproperty.svg?style=flat
[travis-url]: https://travis-ci.org/heycalmdown/virtualproperty
