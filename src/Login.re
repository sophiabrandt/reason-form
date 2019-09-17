let str = ReasonReact.string;

[@react.component]
let make = () => {
  let logger = () => Js.log("Form submitted");

  let (state, handleChange, handleSubmit) = Form.useForm(logger);

  <div className="section is-fullheight">
    <div className="container">
      <div className="column is-4 is-offset-4">
        <div className="box">
          <form
            onSubmit={handleSubmit}>
            <div className="field">
              <label className="label"> {"Username" |> str} </label>
              <div className="control">
                <input
                  className="input"
                  type_="text"
                  name="username"
                  value={state.username}
                  required=true
                  onChange={handleChange}
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
                  onChange={handleChange}
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
