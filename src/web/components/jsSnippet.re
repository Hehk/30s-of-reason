open Utils;

module JsSnippetQuery = [%graphql
  {|
query getJsSnippet($id: ID!) {
  snippet(id: $id) {
    jsOutput
  }
}
|}
];


let component = ReasonReact.statelessComponent("JsSnippet");

let make = (~query as q, ~id, _children) => {
  ...component,
  render: _self => {
    let query = JsSnippetQuery.make(~id, ());
    module Query = (val q : Apollo.Query);
    <Query query>
      ...(
           (response, parse) =>
             switch response {
             | Loading => ele_of_str("loading")
             | Failed(_error) => ele_of_str("error")
             | Loaded(result) =>
               let snippet = parse(result)##snippet;
               <Code text=snippet##jsOutput language="js" />;
             }
         )
    </Query>;
  }
};
