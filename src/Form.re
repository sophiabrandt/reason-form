type state = {
  email: string,
  password: string,
  username: string,
};

let initialState = {email: "", password: "", username: ""};

type action =
  | SetEmail(string)
  | SetPassword(string)
  | SetUsername(string)
  | ResetState;

let reducer = (state, action) => {
  switch (action) {
    | SetEmail(email) => {...state, email}
    | SetPassword(password) => {...state, password}
    | SetUsername(username) => {...state, username}
    | ResetState => initialState;
  }
};

let useForm = (callback) => {
  let valueFromEvent = evt: string => evt->ReactEvent.Form.target##value;
  let nameFromEvent = evt:string => evt->ReactEvent.Form.target##name;

  let (state, dispatch) = React.useReducer(reducer,initialState);

  let handleChange = (evt) => { 
    ReactEvent.Form.persist(evt);
    switch (nameFromEvent(evt)) {
      | "email" => valueFromEvent(evt)->SetEmail |> dispatch;
      | "password" => valueFromEvent(evt)->SetPassword |> dispatch;
      | "username" => valueFromEvent(evt)->SetUsername |> dispatch;
      | _ => ();
    };
  };

  let handleSubmit = (evt) => {
    ReactEvent.Form.preventDefault(evt);
    callback();
    dispatch(ResetState);
  };
  (state, handleChange, handleSubmit);
};
