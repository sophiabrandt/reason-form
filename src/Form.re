[%%debugger.chrome];
let str = ReasonReact.string;

let initialState: FormTypes.formState = {
  username: "",
  email: "",
  password: "",
};

type action =
  | SetUsername(string)
  | SetEmail(string)
  | SetPassword(string)
  | ResetState;

let reducer = (state: FormTypes.formState, action) =>
  switch (action) {
  | SetUsername(username) => {...state, username}
  | SetEmail(email) => {...state, email}
  | SetPassword(password) => {...state, password}
  | ResetState => initialState
  };

let useForm = (~formType, ~callback) => {
  let valueFromEvent = evt: string => evt->ReactEvent.Form.target##value;
  let nameFromEvent = evt: string => evt->ReactEvent.Form.target##name;

  let (formRules, validate) = FormValidation.useValidation(~formType);
  let (valid, setIsValid) = React.useState(() => false);
  let (state, dispatch) = React.useReducer(reducer, initialState);

  React.useEffect2(
    () =>
      valid ?
        {
          callback();
          dispatch(ResetState);
          None;
        } :
        None,
    (formRules, valid),
  );

  let allValid = (~formRules) =>
    Belt.Array.every(formRules, rule => rule.FormTypes.valid);

  let handleChange = evt => {
    ReactEvent.Form.persist(evt);
    switch (nameFromEvent(evt)) {
    | "username" => valueFromEvent(evt)->SetUsername |> dispatch
    | "email" => valueFromEvent(evt)->SetEmail |> dispatch
    | "password" => valueFromEvent(evt)->SetPassword |> dispatch
    | _ => ()
    };
    validate(~formData=state);
  };

  let handleSubmit = evt => {
    ReactEvent.Form.preventDefault(evt);
    setIsValid(_ => allValid(~formRules));
  };

  (state, formRules, handleChange, handleSubmit);
};

module FormErrors = {
  [@react.component]
  let make = (~formRules: FormTypes.formRules) =>
    <div>
      <ul>
        {
          Array.map(
            rule =>
              <li
                key={rule.FormTypes.id |> string_of_int}
                className={
                  rule.valid ?
                    "is-success help is-size-6" : "is-danger help is-size-6"
                }>
                <i className={rule.valid ? "fas fa-check" : "fas fa-times"} />
                {" " |> str}
                {rule.FormTypes.message |> str}
              </li>,
            formRules,
          )
          |> React.array
        }
      </ul>
    </div>;
};

[@react.component]
let make = (~formType) => {
  let logger = () => Js.log("Form submitted");

  let (state, formRules, handleChange, handleSubmit) =
    useForm(~formType, ~callback=logger);

  <div className="section is-fullheight">
    <div className="container">
      <div className="column is-4 is-offset-4">
        <h1 className="is-size-1 has-text-centered is-capitalized">
          {formType |> str}
        </h1>
        <br />
        {
          switch (formRules) {
          | [||] => ReasonReact.null
          | _ => <FormErrors formRules />
          }
        }
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
