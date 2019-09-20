let initialState: FormData.validationErrors = {errors: []};

type action =
  | UsernameRequired(string);

let reducer = (state:FormData.validationErrors, action) =>
  switch (action) {
  | UsernameRequired(_username) => 
    // TODO: implement form validation rules
  let error: FormData.validationError = {field: "username", message: "Username must be at least 5 characters"};
  let newState: FormData.validationErrors = {errors: [error, ...state.errors]};
  Js.log(newState);
  newState;
  };

let useValidation = (~formType) => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  let validate = (~formData: FormData.formState) =>
    if (formType === "register") {
      dispatch(UsernameRequired(formData.username));
    };

  (state, validate);
};
