[%%debugger.chrome%];
let str = ReasonReact.string;

let initialFormData: FormTypes.formState = {
  username: "",
  email: "",
  password: "",
};

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
    username |> String.length >= 5 ?
      {
        state[0].valid = true;
        state;
      } :
      {
        state[0].valid = false;
        state;
      }
  | EmailLongEnough(email) =>
    email |> String.length >= 5 ?
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
  | ResetState => initialFormData
  };

let useForm = (~formType, ~callback) => {
  let valueFromEvent = evt: string => evt->ReactEvent.Form.target##value;
  let nameFromEvent = evt: string => evt->ReactEvent.Form.target##name;

  let (isSubmitting, setIsSubmitting) = React.useState(() => false);
  let (allValid, setAllValid) = React.useState(() => false);
  let (formData, dispatch) = React.useReducer(formReducer, initialFormData);
  let (formRules, dispatchFormRules) =
    React.useReducer(registerFormRulesReducer, registerFormRules);

  let validate = (~formData=formData, ()) =>
    switch (formType) {
    | "register" =>
      formData.username->UsernameLongEnough |> dispatchFormRules;
      formData.email->EmailLongEnough |> dispatchFormRules;
      formData.email->EmailForRegistrationValid |> dispatchFormRules;
      formData.password->PasswordLongEnough |> dispatchFormRules;
    | "login" =>
      /* formData.email->EmailRequired |> dispatchFormRules; */
      /* formData.email->EmailForLoginValid |> dispatchFormRules; */
      /* formData.password->PasswordRequired |> dispatchFormRules; */
      ()
    | _ => ()
    };

  let handleChange = evt => {
    ReactEvent.Form.persist(evt);
    switch (nameFromEvent(evt)) {
    | "username" => valueFromEvent(evt)->SetUsername |> dispatch
    | "email" => valueFromEvent(evt)->SetEmail |> dispatch
    | "password" => valueFromEvent(evt)->SetPassword |> dispatch
    | _ => ()
    };
  };

  React.useEffect2(
    () => {
      validate(~formData, ());
      Js.log(formData);
      allValid && isSubmitting ?
        {
          callback();
          dispatch(ResetState);
          setIsSubmitting(_ => false);
          None;
        } :
        {
          setIsSubmitting(_ => false);
          None;
        };
    },
    (formData, allValid),
  );

  let handleSubmit = evt => {
    ReactEvent.Form.preventDefault(evt);
    setAllValid(_ => areAllRulesValid(~formRules));
    setIsSubmitting(_ => true);
  };

  (formData, formRules, handleChange, handleSubmit);
};
