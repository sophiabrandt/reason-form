type formState = {
  username: string,
  email: string,
  password: string,
};

type validationError = {
  id: int,
  field: string,
  message: string,
};

type validationErrors = list(validationError);
