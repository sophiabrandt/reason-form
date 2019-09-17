[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  switch (url.path) {
    | ["login"] => <Form formType="login"/>
    | ["register"] => <Form formType="register"/>
    | [] => <Main />
    | _ => <NotFoundPage />
    }
}
