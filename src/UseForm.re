let initialFormData: FormTypes.formState = {
  username: "",
  email: "",
  password: "",
};

let registerFormRules: FormTypes.formRules = [|
  {
    id: 0,
    field: "username",
    message: "Username must have at least 5 characters.",
    valid: false,
  },
  {
    id: 1,
    field: "email",
    message: "Email must have at least 5 characters.",
    valid: false,
  },
  {
    id: 2,
    field: "email",
    message: "Email must be a valid email address.",
    valid: false,
  },
  {
    id: 3,
    field: "password",
    message: "Password must have at least 10 characters.",
    valid: false,
  },
|];

let loginFormRules: FormTypes.formRules = [|
  {id: 0, field: "email", message: "Email is required.", valid: false},
  {
    id: 1,
    field: "email",
    message: "Email must be a valid email address.",
    valid: false,
  },
  {id: 2, field: "password", message: "Password is required.", valid: false},
|];

let validEmail = email => {
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

let setRuleToValid = (rules: FormTypes.formRules, id) =>
  Array.map(
    rule => rule.FormTypes.id === id ? {...rule, valid: true} : rule,
    rules,
  );

let setRuleToInvalid = (rules: FormTypes.formRules, id) =>
  Array.map(
    rule => rule.FormTypes.id === id ? {...rule, valid: false} : rule,
    rules,
  );

let registerFormRulesReducer =
    (state: FormTypes.formRules, action: registerFormRulesAction) =>
  switch (action) {
  | UsernameLongEnough(username) =>
    username |> String.length >= 5 ?
      setRuleToValid(state, 0) : setRuleToInvalid(state, 0)
  | EmailLongEnough(email) =>
    email |> String.length >= 5 ?
      setRuleToValid(state, 1) : setRuleToInvalid(state, 1)
  | EmailForRegistrationValid(email) =>
    email |> validEmail ?
      setRuleToValid(state, 2) : setRuleToInvalid(state, 2)
  | PasswordLongEnough(password) =>
    password |> String.length >= 10 ?
      setRuleToValid(state, 3) : setRuleToInvalid(state, 3)
  };

let loginFormRulesReducer =
    (state: FormTypes.formRules, action: loginFormRulesAction) =>
  switch (action) {
  | EmailRequired(email) =>
    email |> String.length > 0 ?
      setRuleToValid(state, 0) : setRuleToInvalid(state, 0)
  | EmailForLoginValid(email) =>
    email |> validEmail ?
      setRuleToValid(state, 1) : setRuleToInvalid(state, 1)
  | PasswordRequired(password) =>
    password |> String.length > 0 ?
      setRuleToValid(state, 2) : setRuleToInvalid(state, 2)
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
  let (formData, dispatchFormData) =
    React.useReducer(formReducer, initialFormData);

  let (registerFormRules, dispatchRegisterFormRules) =
    React.useReducer(registerFormRulesReducer, registerFormRules);
  let (loginFormRules, dispatchLoginFormRules) =
    React.useReducer(loginFormRulesReducer, loginFormRules);

  let formRules =
    switch (formType) {
    | "register" => registerFormRules
    | "login" => loginFormRules
    | _ => [||]
    };

  let validate = (~formData=formData, ()) =>
    switch (formType) {
    | "register" =>
      formData.username->UsernameLongEnough |> dispatchRegisterFormRules;
      formData.email->EmailLongEnough |> dispatchRegisterFormRules;
      formData.email->EmailForRegistrationValid |> dispatchRegisterFormRules;
      formData.password->PasswordLongEnough |> dispatchRegisterFormRules;
    | "login" =>
      formData.email->EmailRequired |> dispatchLoginFormRules;
      formData.email->EmailForLoginValid |> dispatchLoginFormRules;
      formData.password->PasswordRequired |> dispatchLoginFormRules;
    | _ => ()
    };

  let handleChange = evt => {
    ReactEvent.Form.persist(evt);
    switch (nameFromEvent(evt)) {
    | "username" => valueFromEvent(evt)->SetUsername |> dispatchFormData
    | "email" => valueFromEvent(evt)->SetEmail |> dispatchFormData
    | "password" => valueFromEvent(evt)->SetPassword |> dispatchFormData
    | _ => ()
    };
  };

  let handleSubmit = evt => {
    ReactEvent.Form.preventDefault(evt);
    setAllValid(_ => areAllRulesValid(~formRules));
    setIsSubmitting(_ => true);
  };

  React.useEffect1(
    () => {
      validate(~formData, ());
      None;
    },
    [|formData|],
  );

  React.useEffect2(
    () =>
      allValid && isSubmitting ?
        {
          callback();
          dispatchFormData(ResetState);
          setIsSubmitting(_ => false);
          None;
        } :
        {
          setIsSubmitting(_ => false);
          None;
        },
    (allValid, isSubmitting),
  );

  (formData, formRules, handleChange, handleSubmit);
};
