type formState = {
  username: string,
  email: string,
  password: string,
};

type formRule = {
  id: int,
  field: string,
  message: string,
  mutable valid: bool,
};

type formRules = array(formRule);
