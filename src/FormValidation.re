[%%debugger.chrome];

let noFormRules: FormTypes.formRules = [||];

let registerFormRules: FormTypes.formRules = [|
  {
    id: 1,
    field: "username",
    message: "Username must have at least 5 characters.",
    valid: false,
  },
  {
    id: 2,
    field: "email",
    message: "Email must have at least 5 characters.",
    valid: false,
  },
  {
    id: 3,
    field: "email",
    message: "Email must be a valid email address.",
    valid: false,
  },
  {
    id: 4,
    field: "password",
    message: "Password must have at least 10 characters.",
    valid: false,
  },
|];

let loginFormRules: FormTypes.formRules = [|
  {id: 1, field: "email", message: "Email is required.", valid: false},
  {id: 2, field: "password", message: "Password is required.", valid: false},
|];

let validateEmail = email => {
  let re = [%bs.re
    "/^(([^<>()\[\]\\.,;:\s@']+(\.[^<>()\[\]\\.,;:\s@']+)*)|('.+'))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/"
  ];
  email |> Js.Re.test_(re);
};

type action =
  | UsernameLongEnough(string)
  | EmailLongEnough(string)
  | EmailValid(string)
  | PasswordLongEnough(string)
  | EmailRequired(string)
  | PasswordRequired(string);

let reducer = (state: FormTypes.formRules, action) =>
  switch (action) {
  | UsernameLongEnough(username) =>
    username |> String.length >= 5 ?
      {
        state[0].valid = true;
        state;
      } :
      state
  | EmailLongEnough(email) =>
    email |> String.length >= 5 ?
      {
        state[1].valid = true;
        state;
      } :
      state
  | EmailValid(email) =>
    email |> validateEmail ?
      {
        state[2].valid = true;
        state;
      } :
      state
  | PasswordLongEnough(password) =>
    password |> String.length >= 10 ?
      {
        state[3].valid = true;
        state;
      } :
      state
  | EmailRequired(email) =>
    email |> String.length > 0 ?
      {
        state[0].valid = true;
        state;
      } :
      state
  | PasswordRequired(password) =>
    password |> String.length > 0 ?
      {
        state[1].valid = true;
        state;
      } :
      state
  };

let useValidation = (~formType) =>
  switch (formType) {
  | "register" =>
    let (state, dispatch) = React.useReducer(reducer, registerFormRules);
    let validate =
        (~formData as {username, email, password}: FormTypes.formState) => {
      username->UsernameLongEnough |> dispatch;
      email->EmailLongEnough |> dispatch;
      email->EmailValid |> dispatch;
      password->PasswordLongEnough |> dispatch;
    };
    (state, validate);
  | "login" =>
    let (state, dispatch) = React.useReducer(reducer, loginFormRules);
    let validate = (~formData as {email, password}: FormTypes.formState) => {
      email->EmailRequired |> dispatch;
      password->PasswordRequired |> dispatch;
    };
    (state, validate);
  | _ =>
    let (state, _dispatch) = React.useReducer(reducer, noFormRules);
    let validate = (~formData as _: FormTypes.formState) => ();
    (state, validate);
  };
