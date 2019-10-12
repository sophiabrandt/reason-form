// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Caml_chrome_debugger from "bs-platform/lib/es6/caml_chrome_debugger.js";
import * as UseForm$ReactHooksTemplate from "./UseForm.bs.js";

function str(prim) {
  return prim;
}

function Form$FormErrors(Props) {
  var formRules = Props.formRules;
  return React.createElement("div", undefined, React.createElement("ul", undefined, Belt_Array.map(formRules, (function (rule) {
                        var match = rule[/* valid */3];
                        var match$1 = rule[/* valid */3];
                        return React.createElement("li", {
                                    key: String(rule[/* id */0]),
                                    className: match ? "is-success help is-size-6" : "is-danger help is-size-6"
                                  }, React.createElement("i", {
                                        className: match$1 ? "fas fa-check" : "fas fa-times"
                                      }), " ", rule[/* message */2]);
                      }))));
}

var FormErrors = /* module */Caml_chrome_debugger.localModule(["make"], [Form$FormErrors]);

function Form(Props) {
  var formType = Props.formType;
  var logger = function (param) {
    console.log("Form submitted");
    return /* () */0;
  };
  var match = UseForm$ReactHooksTemplate.useForm(formType, logger);
  var handleChange = match[2];
  var formRules = match[1];
  var state = match[0];
  var match$1 = formType === "register";
  return React.createElement("div", {
              className: "section is-fullheight"
            }, React.createElement("div", {
                  className: "container"
                }, React.createElement("div", {
                      className: "column is-4 is-offset-4"
                    }, React.createElement("h1", {
                          className: "is-size-1 has-text-centered is-capitalized"
                        }, formType), React.createElement("br", undefined), formRules.length !== 0 ? React.createElement(Form$FormErrors, {
                            formRules: formRules
                          }) : null, React.createElement("br", undefined), React.createElement("div", {
                          className: "box"
                        }, React.createElement("form", {
                              onSubmit: match[3]
                            }, match$1 ? React.createElement("div", {
                                    className: "field"
                                  }, React.createElement("label", {
                                        className: "label"
                                      }, "Username"), React.createElement("div", {
                                        className: "control"
                                      }, React.createElement("input", {
                                            className: "input",
                                            name: "username",
                                            required: true,
                                            type: "text",
                                            value: state[/* username */0],
                                            onChange: handleChange
                                          }))) : null, React.createElement("div", {
                                  className: "field"
                                }, React.createElement("label", {
                                      className: "label"
                                    }, "Email Address"), React.createElement("div", {
                                      className: "control"
                                    }, React.createElement("input", {
                                          className: "input",
                                          name: "email",
                                          required: true,
                                          type: "email",
                                          value: state[/* email */1],
                                          onChange: handleChange
                                        }))), React.createElement("div", {
                                  className: "field"
                                }, React.createElement("label", {
                                      className: "label"
                                    }, "Password"), React.createElement("div", {
                                      className: "control"
                                    }, React.createElement("input", {
                                          className: "input",
                                          name: "password",
                                          required: true,
                                          type: "password",
                                          value: state[/* password */2],
                                          onChange: handleChange
                                        }))), React.createElement("button", {
                                  className: "button is-block is-info is-fullwidth is-uppercase",
                                  type: "submit"
                                }, formType, React.createElement("br", undefined)))), React.createElement("a", {
                          className: "is-size-4",
                          href: "/"
                        }, "⬅️ Back to Homepage"))));
}

var make = Form;

export {
  str ,
  FormErrors ,
  make ,
  
}
/* react Not a pure module */
