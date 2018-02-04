open Utils;

let component = ReasonReact.statelessComponent("SnippetsLoading");

let make = (_children) => {
  ...component,
    render: (_self) => <div>(str_to_ele("loading snippets"))</div>
};
