// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

function Input(Props) {
  var onSubmit = Props.onSubmit;
  var match = React.useReducer((function (_oldText, newText) {
          return newText;
        }), "");
  var setText = match[1];
  var text = match[0];
  return React.createElement("input", {
              className: "input is-primary is-large",
              placeholder: "Write something to do",
              type: "text",
              value: text,
              onKeyDown: (function (evt) {
                  if (evt.key === "Enter") {
                    Curry._1(onSubmit, text);
                    return Curry._1(setText, "");
                  } else {
                    return 0;
                  }
                }),
              onChange: (function (evt) {
                  return Curry._1(setText, evt.target.value);
                })
            });
}

var make = Input;

exports.make = make;
/* react Not a pure module */
