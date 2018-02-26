module type Client = {
  module type Query = {
    type response =
      | Loading
      | Loaded(Js.Json.t)
      | Failed(string);
    type state = {
      response,
      variables: Js.Json.t
    };
    type action =
      | Result(string)
      | Error(string);
    let sendQuery: (~query: 'query, ~reducer: 'reduce) => unit;
    let component:
      string =>
      ReasonReact.componentSpec(
        state,
        ReasonReact.stateless,
        ReasonReact.noRetainedProps,
        ReasonReact.noRetainedProps,
        action
      );
    let make: (~query: 'query, 'children) => ReasonReact.reactClass;
  };
  module type Mutation = {};
};

module type Query = {
  type response =
    | Loading
    | Loaded(Js.Json.t)
    | Failed(string);
  type state = {
    response,
    variables: Js.Json.t
  };
  type action =
    | Result(string)
    | Error(string);
  let sendQuery:
    (
      ~query: {
                ..
                "query": string,
                "variables": Js.Json.t
              },
      ~reduce: (unit => action, unit) => 'a
    ) =>
    unit;
  let component:
    ReasonReact.componentSpec(
      state,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      action
    );
  let make:
    (
      ~query: {
                ..
                "query": string,
                "variables": Js.Json.t,
                "parse": 'a
              },
      (response, 'a) => ReasonReact.reactElement
    ) =>
    ReasonReact.componentSpec(
      state,
      state,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      action
    );
};

type apolloState =
  | None
  | Some((module Query));

module Context =
  ReasonReactContext.CreateContext(
    {
      type state = apolloState;
      let name = "Apollo";
      let defaultValue = None;
    }
  );
