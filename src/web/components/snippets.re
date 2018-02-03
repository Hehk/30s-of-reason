open Utils;

module SnippetQuery = [%graphql {|
  query getAllSnippets($filter: String!) {
    allSnippets(query: $filter) {
      content
    }
  }
|}
];

module Query = Apollo.Client.Query;

let component = ReasonReact.statelessComponent("snippets");

let make = _children => {
  ...component,
  render: _self => {
    let snippetQuery = SnippetQuery.make(~filter="reduce", ());
    <Query query=snippetQuery>
      ...(
           (response, _parse) =>
             switch response {
             | Loading => <div> (str_to_ele("loading")) </div>
             | Failed(_error) => <div> (str_to_ele("loading")) </div>
             | Loaded(result) =>
               Js.log(result);
               <div> (str_to_ele("it works")) </div>;
             }
         )
    </Query>;
  }
};
