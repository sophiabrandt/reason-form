let str = ReasonReact.string;

type state = {
  email: string,
  password: string,
};

type action =
  | SetEmail(string)
  | SetPassword(string)
  | SubmitForm;

[@react.component]
let make = () => {
  let initialState = {email: "", password: ""};

  let (_state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | SetEmail(email) => {...state, email}
        | SetPassword(password) => {...state, password}
        | SubmitForm =>
          Js.log({j|Form submitted with values: $state|j});
          state;
        },
        initialState
    );

  let valueFromEvent = evt: string => evt->ReactEvent.Form.target##value;

  <div className="section is-fullheight">
    <div className="container">
      <div className="column is-4 is-offset-4">
        <div className="box">
          <form
            onSubmit={
              evt => {
                ReactEvent.Form.preventDefault(evt);
                dispatch(SubmitForm);
              }
            }>
            <div className="field">
              <label className="label"> {"Email Address" |> str} </label>
              <div className="control">
                <input
                  className="input"
                  type_="email"
                  name="email"
                  required=true
                  onChange={evt => valueFromEvent(evt)->SetEmail |> dispatch}
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
                  required=true
                  onChange={
                    evt => valueFromEvent(evt)->SetPassword |> dispatch
                  }
                />
              </div>
            </div>
            <button
              type_="submit" className="button is-block is-info is-fullwidth">
              {"Login" |> str}
            </button>
          </form>
        </div>
      </div>
    </div>
  </div>;
};
