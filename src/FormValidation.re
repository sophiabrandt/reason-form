[%%debugger.chrome];
let initialState: FormTypes.validationErrors = [];

type action =
  | UsernameRequired(string);

let reducer = (state: FormTypes.validationErrors, action) =>
  switch (action) {
  | UsernameRequired(username) =>
    username |> String.length < 5 ?
      {
        let error: FormTypes.validationError = {
          id: 1,
          field: "username",
          message: "Username must be at least 5 characters",
          valid: false,
        };
        let newState: FormTypes.validationErrors = [error, ...state];
        newState;
      } :
      state
  };

let useValidation = (~formType) => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  let validate = (~formData: FormTypes.formState) =>
    if (formType === "register") {
      formData.username->UsernameRequired |> dispatch;
    };

  (state, validate);
};
