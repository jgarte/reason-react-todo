// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Uuid = require("bs-guid/src/Uuid.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Item$ReactHooksTemplate = require("./Item.bs.js");
var Todo$ReactHooksTemplate = require("./Todo.bs.js");
var Input$ReactHooksTemplate = require("./Input.bs.js");

function str(prim) {
  return prim;
}

var uuidv4 = Uuid.V4.uuidv4;

var initialState = {
  items: /* :: */[
    {
      id: uuidv4(/* () */0),
      title: "Buy milk",
      completed: false
    },
    /* [] */0
  ]
};

function reducer(state, action) {
  switch (action.tag | 0) {
    case /* AddItem */0 :
        return {
                items: /* :: */[
                  Item$ReactHooksTemplate.newItem(action[0]),
                  state.items
                ]
              };
    case /* ToggleItem */1 :
        var id = action[0];
        var items = List.map((function (item) {
                var match = item.id === id;
                if (match) {
                  return {
                          id: item.id,
                          title: item.title,
                          completed: !item.completed
                        };
                } else {
                  return item;
                }
              }), state.items);
        return {
                items: items
              };
    case /* DeleteItem */2 :
        var id$1 = action[0];
        var items$1 = List.filter((function (item) {
                  return item.id !== id$1;
                }))(state.items);
        return {
                items: items$1
              };
    
  }
}

function App(Props) {
  var match = Props.title;
  var title = match !== undefined ? match : "What to do";
  var match$1 = React.useReducer(reducer, initialState);
  var dispatch = match$1[1];
  var items = match$1[0].items;
  var numItems = List.length(items);
  return React.createElement(React.Fragment, undefined, React.createElement("div", {
                  className: "section is-tall"
                }, React.createElement("header", {
                      className: "title has-text-centered"
                    }, title), React.createElement("main", {
                      className: "container is-tall-container"
                    }, React.createElement("div", {
                          className: "field"
                        }, React.createElement(Input$ReactHooksTemplate.make, {
                              onSubmit: (function (text) {
                                  return Curry._1(dispatch, /* AddItem */Block.__(0, [text]));
                                })
                            })), React.createElement("ol", {
                          className: "box list"
                        }, $$Array.of_list(List.map((function (item) {
                                    return React.createElement(Todo$ReactHooksTemplate.make, {
                                                item: item,
                                                label: item.title,
                                                onToggle: (function (param) {
                                                    return Curry._1(dispatch, /* ToggleItem */Block.__(1, [item.id]));
                                                  }),
                                                onDelete: (function (param) {
                                                    return Curry._1(dispatch, /* DeleteItem */Block.__(2, [item.id]));
                                                  }),
                                                key: item.id
                                              });
                                  }), items)))), React.createElement("footer", undefined, React.createElement("p", {
                          className: "content has-text-left"
                        }), String(numItems), " items")));
}

var make = App;

exports.str = str;
exports.uuidv4 = uuidv4;
exports.initialState = initialState;
exports.reducer = reducer;
exports.make = make;
/* initialState Not a pure module */
