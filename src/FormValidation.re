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
    message: "Password must be greater than 10 characters.",
    valid: false,
  },
|];

let loginFormRules: FormTypes.formRules = [|
  {id: 5, field: "email", message: "Email is required.", valid: false},
  {id: 6, field: "password", message: "Password is required.", valid: false},
|];

type action =
  | UsernameLongEnough(string)
  | EmailLongEnough(string);

let reducer = (state: FormTypes.formRules, action) =>
  switch (action) {
  | UsernameLongEnough(username) =>
    username |> String.length > 4 ?
      {
        state[0].valid = true;
        state;
      } :
      state
  | EmailLongEnough(email) =>
    email |> String.length > 4 ?
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
    };
    (state, validate);
  | "login" =>
    let (state, dispatch) = React.useReducer(reducer, loginFormRules);
    let validate = (~formData: FormTypes.formState) => ();
    (state, validate);
  | _ =>
    let (state, dispatch) = React.useReducer(reducer, noFormRules);
    let validate = (~formData: FormTypes.formState) => ();
    (state, validate);
  };
