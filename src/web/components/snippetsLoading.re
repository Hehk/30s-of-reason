open Utils;

let component = ReasonReact.statelessComponent("SnippetsLoading");

let make = (_children) => {
  ...component,
    render: (_self) => <div>(ele_of_str("loading snippets"))</div>
};
