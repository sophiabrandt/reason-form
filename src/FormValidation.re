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
  {
    id: 2,
    field: "email",
    message: "Email must be a valid email address.",
    valid: false,
  },
  {id: 3, field: "password", message: "Password is required.", valid: false},
|];

let validateEmail = email => {
  let re = [%bs.re
    "/^(([^<>()\[\]\\.,;:\s@']+(\.[^<>()\[\]\\.,;:\s@']+)*)|('.+'))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/"
  ];
  email |> Js.Re.test_(re);
};

type registerFormRulesAction =
  | UsernameLongEnough(string)
  | EmailLongEnough(string)
  | EmailForRegistrationValid(string)
  | PasswordLongEnough(string);

type loginFormRulesAction =
  | EmailRequired(string)
  | EmailForLoginValid(string)
  | PasswordRequired(string);

let registerFormRulesReducer =
    (state: FormTypes.formRules, action: registerFormRulesAction) =>
  switch (action) {
  | UsernameLongEnough(username) =>
    username |> String.length >= 4 ?
      {
        state[0].valid = true;
        state;
      } :
      {
        state[0].valid = false;
        state;
      }
  | EmailLongEnough(email) =>
    email |> String.length >= 4 ?
      {
        state[1].valid = true;
        state;
      } :
      {
        state[1].valid = false;
        state;
      }
  | EmailForRegistrationValid(email) =>
    email |> validateEmail ?
      {
        state[2].valid = true;
        state;
      } :
      {
        state[2].valid = false;
        state;
      }
  | PasswordLongEnough(password) =>
    password |> String.length >= 9 ?
      {
        state[3].valid = true;
        state;
      } :
      {
        state[3].valid = false;
        state;
      }
  };

let loginFormRulesReducer =
    (state: FormTypes.formRules, action: loginFormRulesAction) =>
  switch (action) {
  | EmailRequired(email) =>
    email |> String.length > 0 ?
      {
        state[0].valid = true;
        state;
      } :
      {
        state[0].valid = false;
        state;
      }
  | EmailForLoginValid(email) =>
    email |> validateEmail ?
      {
        state[1].valid = true;
        state;
      } :
      {
        state[1].valid = false;
        state;
      }
  | PasswordRequired(password) =>
    password |> String.length > 0 ?
      {
        state[2].valid = true;
        state;
      } :
      {
        state[2].valid = false;
        state;
      }
  };

let useValidation = (~formType) =>
  switch (formType) {
  | "register" =>
    let (state, dispatch) =
      React.useReducer(registerFormRulesReducer, registerFormRules);
    let validate =
        (~formData as {username, email, password}: FormTypes.formState) => {
      username->UsernameLongEnough |> dispatch;
      email->EmailLongEnough |> dispatch;
      email->EmailForRegistrationValid |> dispatch;
      password->PasswordLongEnough |> dispatch;
    };
    (state, validate);
  | "login" =>
    let (state, dispatch) =
      React.useReducer(loginFormRulesReducer, loginFormRules);
    let validate = (~formData as {email, password}: FormTypes.formState) => {
      email->EmailRequired |> dispatch;
      email->EmailForLoginValid |> dispatch;
      password->PasswordRequired |> dispatch;
    };
    (state, validate);
  | _ =>
    let state: FormTypes.formRules = [||];
    let validate = (~formData as _: FormTypes.formState) => ();
    (state, validate);
  };
