//This is the entry point for node to rust communication

var addon = require('../native');

console.log(addon.hello());

module.hello = addon.hello;