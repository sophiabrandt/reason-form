[%%debugger.chrome];
let initialState: FormData.validationErrors = {errors: []};

type action =
  | UsernameRequired(string);

let reducer = (state: FormData.validationErrors, action) =>
  switch (action) {
  | UsernameRequired(username) =>
    username |> String.length < 5 ?
      {
        let error: FormData.validationError = {
          field: "username",
          message: "Username must be at least 5 characters",
        };
        let newState: FormData.validationErrors = {
          errors: [error, ...state.errors],
        };
        newState;
      } :
      state
  };

let useValidation = (~formType) => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  let validate = (~formData: FormData.formState) =>
    if (formType === "register") {
      formData.username->UsernameRequired |> dispatch;
    };

  (state, validate);
};
