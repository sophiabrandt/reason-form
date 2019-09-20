type formState = {
  username: string,
  email: string,
  password: string,
};

type validationError = {
  field: string,
  message: string,
};

type validationErrors = {errors: list(validationError)};
