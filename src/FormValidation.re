type error = {
  field: string,
  message: string,
};

type state = {errors: list(error)};

let initialState = {errors: []};

type action =
  | UsernameRequired(string);

let reducer = (state, action) =>
  switch (action) {
  | UsernameRequired(_username) => {
    // TODO: implement form validation rules
      errors: [
        {field: "username", message: "Username must be at least 5 characters."},
        ...state.errors,
      ],
    }
  };

let useValidation = (~formType) => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  let validate = (~formData:Form.state) =>
    if (formType === "login") {
      dispatch(UsernameRequired(formData.username));
    };

  (state, validate);
};
