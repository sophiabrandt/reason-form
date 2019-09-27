let str = ReasonReact.string;

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

let areAllRulesValid = (~formRules) =>
  Belt.Array.every(formRules, rule => rule.FormTypes.valid);

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
    let allValid = areAllRulesValid(state);
    (state, validate, allValid);
  | "login" =>
    let (state, dispatch) =
      React.useReducer(loginFormRulesReducer, loginFormRules);
    let validate = (~formData as {email, password}: FormTypes.formState) => {
      email->EmailRequired |> dispatch;
      email->EmailForLoginValid |> dispatch;
      password->PasswordRequired |> dispatch;
    };
    let allValid = areAllRulesValid(state);
    (state, validate, allValid);
  | _ =>
    let state: FormTypes.formRules = [||];
    let validate = (~formData as _: FormTypes.formState) => ();
    let allValid = false;
    (state, validate, allValid);
  };
let initialState: FormTypes.formState = {
  username: "",
  email: "",
  password: "",
};

type formAction =
  | SetUsername(string)
  | SetEmail(string)
  | SetPassword(string)
  | ResetState;

let formReducer = (state: FormTypes.formState, action: formAction) =>
  switch (action) {
  | SetUsername(username) => {...state, username}
  | SetEmail(email) => {...state, email}
  | SetPassword(password) => {...state, password}
  | ResetState => initialState
  };

let useForm = (~formType, ~callback) => {
  let valueFromEvent = evt: string => evt->ReactEvent.Form.target##value;
  let nameFromEvent = evt: string => evt->ReactEvent.Form.target##name;

  let (formRules, validate, allValid) = useValidation(~formType);
  let (isSubmitting, setIsSubmitting) = React.useState(() => false);
  let (state, dispatch) = React.useReducer(formReducer, initialState);

  React.useEffect2(
    () =>
      isSubmitting && allValid ?
        {
          callback();
          dispatch(ResetState);
          None;
        } :
        {
          setIsSubmitting(_ => false);
          None;
        },
    (isSubmitting, allValid),
  );

  let handleChange = evt => {
    ReactEvent.Form.persist(evt);
    switch (nameFromEvent(evt)) {
    | "username" => valueFromEvent(evt)->SetUsername |> dispatch
    | "email" => valueFromEvent(evt)->SetEmail |> dispatch
    | "password" => valueFromEvent(evt)->SetPassword |> dispatch
    | _ => ()
    };
  };

  React.useEffect(() => {
    validate(~formData=state);
    None;
  });

  let handleSubmit = evt => {
    ReactEvent.Form.preventDefault(evt);
    setIsSubmitting(_ => true);
  };

  (state, formRules, handleChange, handleSubmit);
};
