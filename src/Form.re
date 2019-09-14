let str = ReasonReact.string;

type state = {
  email: string,
  password: string,
};

type action =
  | SetEmail(string)
  | SetPassword(string);

[@react.component]
let make = () => {
  let valueFromEvent = evt: string => evt->ReactEvent.Form.target##value;
  let (_state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | SetEmail(email) => {...state, email}
        | SetPassword(password) => {...state, password}
        },
      {email: "", password: ""},
    );
  <div className="section is-fullheight">
    <div className="container">
      <div className="column is-4 is-offset-4">
        <div className="box">
          <form>
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
