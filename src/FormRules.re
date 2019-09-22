[%%debugger.chrome];

let registerFormRules: FormTypes.validationErrors = [
  {
    id: 1,
    field: "username",
    message: "Username must be greater than 5 characters.",
    valid: false,
  },
  {
    id: 2,
    field: "email",
    message: "Email must be greater than 5 characters.",
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
];
