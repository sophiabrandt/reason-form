[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  switch (url.path) {
    | ["login"] => <Login />
    | ["register"] => <Register />
    | [] => <Main />
    | _ => <NotFoundPage />
    }
}
