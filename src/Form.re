[%%debugger.chrome];
let str = ReasonReact.string;

let initialState: FormData.formState = {
  username: "",
  email: "",
  password: "",
};

type action =
  | SetUsername(string)
  | SetEmail(string)
  | SetPassword(string)
  | ResetState;

let reducer = (state: FormData.formState, action) =>
  switch (action) {
  | SetUsername(username) => {...state, username}
  | SetEmail(email) => {...state, email}
  | SetPassword(password) => {...state, password}
  | ResetState => initialState
  };

let useForm = (~formType, ~callback) => {
  let valueFromEvent = evt: string => evt->ReactEvent.Form.target##value;
  let nameFromEvent = evt: string => evt->ReactEvent.Form.target##name;

  let (validationErrors, updatedValidationErrors, validate) =
    FormValidation.useValidation(~formType);
  let (errors, setErrors) = React.useState(() => validationErrors);
  let (isSubmitting, setIsSubmitting) = React.useState(() => false);
  let (state, dispatch) = React.useReducer(reducer, initialState);

  React.useEffect1(
    () =>
      switch (errors.errors) {
      | [] =>
        Js.log("match on empty errors list");
        Js.log(isSubmitting);
        if (isSubmitting) {
          Js.log("submitting");
          callback();
          dispatch(ResetState);
        };
        None;
      | _ =>
        Js.log("no effect");
        ();
        None;
      },
    [|errors.errors|],
  );
  let handleChange = evt => {
    ReactEvent.Form.persist(evt);
    switch (nameFromEvent(evt)) {
    | "username" => valueFromEvent(evt)->SetUsername |> dispatch
    | "email" => valueFromEvent(evt)->SetEmail |> dispatch
    | "password" => valueFromEvent(evt)->SetPassword |> dispatch
    | _ => ()
    };
  };

  let handleSubmit = evt => {
    ReactEvent.Form.preventDefault(evt);
    Js.log("validate function called");
    validate(~formData=state);
    Js.log(errors.errors);
    setIsSubmitting(_ => true);
  };

  (state, errors, handleChange, handleSubmit);
};

[@react.component]
let make = (~formType) => {
  let logger = () => Js.log("Form submitted");

  let (state, errors, handleChange, handleSubmit) =
    useForm(~formType, ~callback=logger);

  <div className="section is-fullheight">
    <div className="container">
      <div className="column is-4 is-offset-4">
        <h1 className="is-size-1 has-text-centered is-capitalized">
          {formType |> str}
        </h1>
        <br />
        <div className="box">
          <form onSubmit=handleSubmit>
            {
              formType === "register" ?
                <div className="field">
                  <label className="label"> {"Username" |> str} </label>
                  <div className="control">
                    <input
                      className="input"
                      type_="text"
                      name="username"
                      value={state.username}
                      required=true
                      onChange=handleChange
                    />
                  </div>
                </div> :
                ReasonReact.null
            }
            <div className="field">
              <label className="label"> {"Email Address" |> str} </label>
              <div className="control">
                <input
                  className="input"
                  type_="email"
                  name="email"
                  value={state.email}
                  required=true
                  onChange=handleChange
                />
              </div>
            </div>
            <div className="field">
              <label className="label"> {"Password" |> str} </label>
              <div className="control">
                <input
                  className="input"
                  type_="password"
                  name="password"
                  value={state.password}
                  required=true
                  onChange=handleChange
                />
              </div>
            </div>
            <button
              type_="submit"
              className="button is-block is-info is-fullwidth is-uppercase">
              {formType |> str}
              <br />
            </button>
          </form>
        </div>
      </div>
    </div>
  </div>;
};
