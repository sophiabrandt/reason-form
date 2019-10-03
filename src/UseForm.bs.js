// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE

import * as $$Array from "bs-platform/lib/es6/array.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Caml_chrome_debugger from "bs-platform/lib/es6/caml_chrome_debugger.js";

var initialFormData = /* record */Caml_chrome_debugger.record([
    "username",
    "email",
    "password"
  ], [
    "",
    "",
    ""
  ]);

var registerFormRules = /* array */[
  /* record */Caml_chrome_debugger.record([
      "id",
      "field",
      "message",
      "valid"
    ], [
      0,
      "username",
      "Username must have at least 5 characters.",
      false
    ]),
  /* record */Caml_chrome_debugger.record([
      "id",
      "field",
      "message",
      "valid"
    ], [
      1,
      "email",
      "Email must have at least 5 characters.",
      false
    ]),
  /* record */Caml_chrome_debugger.record([
      "id",
      "field",
      "message",
      "valid"
    ], [
      2,
      "email",
      "Email must be a valid email address.",
      false
    ]),
  /* record */Caml_chrome_debugger.record([
      "id",
      "field",
      "message",
      "valid"
    ], [
      3,
      "password",
      "Password must have at least 10 characters.",
      false
    ])
];

var loginFormRules = /* array */[
  /* record */Caml_chrome_debugger.record([
      "id",
      "field",
      "message",
      "valid"
    ], [
      0,
      "email",
      "Email is required.",
      false
    ]),
  /* record */Caml_chrome_debugger.record([
      "id",
      "field",
      "message",
      "valid"
    ], [
      1,
      "email",
      "Email must be a valid email address.",
      false
    ]),
  /* record */Caml_chrome_debugger.record([
      "id",
      "field",
      "message",
      "valid"
    ], [
      2,
      "password",
      "Password is required.",
      false
    ])
];

function validateEmail(email) {
  var re = (/^(([^<>()\[\]\.,;:\s@']+(\.[^<>()\[\]\.,;:\s@']+)*)|('.+'))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/);
  return re.test(email);
}

function areAllRulesValid(formRules) {
  return Belt_Array.every(formRules, (function (rule) {
                return rule[/* valid */3];
              }));
}

function setRuleToValid(rules, id) {
  return $$Array.map((function (rule) {
                var match = rule[/* id */0] === id;
                if (match) {
                  return /* record */Caml_chrome_debugger.record([
                            "id",
                            "field",
                            "message",
                            "valid"
                          ], [
                            rule[/* id */0],
                            rule[/* field */1],
                            rule[/* message */2],
                            true
                          ]);
                } else {
                  return rule;
                }
              }), rules);
}

function setRuleToInvalid(rules, id) {
  return $$Array.map((function (rule) {
                var match = rule[/* id */0] === id;
                if (match) {
                  return /* record */Caml_chrome_debugger.record([
                            "id",
                            "field",
                            "message",
                            "valid"
                          ], [
                            rule[/* id */0],
                            rule[/* field */1],
                            rule[/* message */2],
                            false
                          ]);
                } else {
                  return rule;
                }
              }), rules);
}

function registerFormRulesReducer(state, action) {
  switch (action.tag | 0) {
    case 0 : 
        var match = action[0].length >= 5;
        if (match) {
          return setRuleToValid(state, 0);
        } else {
          return setRuleToInvalid(state, 0);
        }
    case 1 : 
        var match$1 = action[0].length >= 5;
        if (match$1) {
          return setRuleToValid(state, 1);
        } else {
          return setRuleToInvalid(state, 1);
        }
    case 2 : 
        var match$2 = validateEmail(action[0]);
        if (match$2) {
          return setRuleToValid(state, 2);
        } else {
          return setRuleToInvalid(state, 2);
        }
    case 3 : 
        var match$3 = action[0].length >= 10;
        if (match$3) {
          return setRuleToValid(state, 3);
        } else {
          return setRuleToInvalid(state, 3);
        }
    
  }
}

function loginFormRulesReducer(state, action) {
  switch (action.tag | 0) {
    case 0 : 
        var match = action[0].length !== 0;
        if (match) {
          return setRuleToValid(state, 0);
        } else {
          return setRuleToInvalid(state, 0);
        }
    case 1 : 
        var match$1 = validateEmail(action[0]);
        if (match$1) {
          return setRuleToValid(state, 1);
        } else {
          return setRuleToInvalid(state, 1);
        }
    case 2 : 
        var match$2 = action[0].length !== 0;
        if (match$2) {
          return setRuleToValid(state, 2);
        } else {
          return setRuleToInvalid(state, 2);
        }
    
  }
}

function formReducer(state, action) {
  if (typeof action === "number") {
    return initialFormData;
  } else {
    switch (action.tag | 0) {
      case 0 : 
          return /* record */Caml_chrome_debugger.record([
                    "username",
                    "email",
                    "password"
                  ], [
                    action[0],
                    state[/* email */1],
                    state[/* password */2]
                  ]);
      case 1 : 
          return /* record */Caml_chrome_debugger.record([
                    "username",
                    "email",
                    "password"
                  ], [
                    state[/* username */0],
                    action[0],
                    state[/* password */2]
                  ]);
      case 2 : 
          return /* record */Caml_chrome_debugger.record([
                    "username",
                    "email",
                    "password"
                  ], [
                    state[/* username */0],
                    state[/* email */1],
                    action[0]
                  ]);
      
    }
  }
}

function useForm(formType, callback) {
  var match = React.useState((function () {
          return false;
        }));
  var setIsSubmitting = match[1];
  var isSubmitting = match[0];
  var match$1 = React.useState((function () {
          return false;
        }));
  var setAllValid = match$1[1];
  var allValid = match$1[0];
  var match$2 = React.useReducer(formReducer, initialFormData);
  var dispatchFormData = match$2[1];
  var formData = match$2[0];
  var match$3 = React.useReducer(registerFormRulesReducer, registerFormRules);
  var dispatchRegisterFormRules = match$3[1];
  var match$4 = React.useReducer(loginFormRulesReducer, loginFormRules);
  var dispatchLoginFormRules = match$4[1];
  var formRules;
  switch (formType) {
    case "login" : 
        formRules = match$4[0];
        break;
    case "register" : 
        formRules = match$3[0];
        break;
    default:
      formRules = /* array */[];
  }
  var validate = function ($staropt$star, param) {
    var formData$1 = $staropt$star !== undefined ? $staropt$star : formData;
    switch (formType) {
      case "login" : 
          Curry._1(dispatchLoginFormRules, /* EmailRequired */Caml_chrome_debugger.variant("EmailRequired", 0, [formData$1[/* email */1]]));
          Curry._1(dispatchLoginFormRules, /* EmailForLoginValid */Caml_chrome_debugger.variant("EmailForLoginValid", 1, [formData$1[/* email */1]]));
          return Curry._1(dispatchLoginFormRules, /* PasswordRequired */Caml_chrome_debugger.variant("PasswordRequired", 2, [formData$1[/* password */2]]));
      case "register" : 
          Curry._1(dispatchRegisterFormRules, /* UsernameLongEnough */Caml_chrome_debugger.variant("UsernameLongEnough", 0, [formData$1[/* username */0]]));
          Curry._1(dispatchRegisterFormRules, /* EmailLongEnough */Caml_chrome_debugger.variant("EmailLongEnough", 1, [formData$1[/* email */1]]));
          Curry._1(dispatchRegisterFormRules, /* EmailForRegistrationValid */Caml_chrome_debugger.variant("EmailForRegistrationValid", 2, [formData$1[/* email */1]]));
          return Curry._1(dispatchRegisterFormRules, /* PasswordLongEnough */Caml_chrome_debugger.variant("PasswordLongEnough", 3, [formData$1[/* password */2]]));
      default:
        return /* () */0;
    }
  };
  var handleChange = function (evt) {
    evt.persist();
    var match = evt.target.name;
    switch (match) {
      case "email" : 
          return Curry._1(dispatchFormData, /* SetEmail */Caml_chrome_debugger.variant("SetEmail", 1, [evt.target.value]));
      case "password" : 
          return Curry._1(dispatchFormData, /* SetPassword */Caml_chrome_debugger.variant("SetPassword", 2, [evt.target.value]));
      case "username" : 
          return Curry._1(dispatchFormData, /* SetUsername */Caml_chrome_debugger.variant("SetUsername", 0, [evt.target.value]));
      default:
        return /* () */0;
    }
  };
  var handleSubmit = function (evt) {
    evt.preventDefault();
    Curry._1(setAllValid, (function (param) {
            return Belt_Array.every(formRules, (function (rule) {
                          return rule[/* valid */3];
                        }));
          }));
    return Curry._1(setIsSubmitting, (function (param) {
                  return true;
                }));
  };
  React.useEffect((function () {
          validate(formData, /* () */0);
          return undefined;
        }), /* array */[formData]);
  React.useEffect((function () {
          var match = allValid && isSubmitting;
          if (match) {
            Curry._1(callback, /* () */0);
            Curry._1(dispatchFormData, /* ResetState */0);
            Curry._1(setIsSubmitting, (function (param) {
                    return false;
                  }));
            return undefined;
          } else {
            Curry._1(setIsSubmitting, (function (param) {
                    return false;
                  }));
            return undefined;
          }
        }), /* tuple */[
        allValid,
        isSubmitting
      ]);
  return /* tuple */[
          formData,
          formRules,
          handleChange,
          handleSubmit
        ];
}

export {
  initialFormData ,
  registerFormRules ,
  loginFormRules ,
  validateEmail ,
  areAllRulesValid ,
  setRuleToValid ,
  setRuleToInvalid ,
  registerFormRulesReducer ,
  loginFormRulesReducer ,
  formReducer ,
  useForm ,
  
}
/* react Not a pure module */
