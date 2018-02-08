open Utils;

module SnippetQuery = [%graphql
  {|
  query getAllSnippets($filter: String!) {
    allSnippets(query: $filter) {
      content,
      title,
      description,
      id
    }
  }
|}
];

module Query = Apollo.Client.Query;

let component = ReasonReact.statelessComponent("snippets");

let make = (~filter="", _children) => {
  ...component,
  render: _self => {
    let snippetQuery = SnippetQuery.make(~filter, ());
    <PageFrame>
      <Query query=snippetQuery>
        ...(
             (response, parse) =>
               switch response {
               | Loading => <SnippetsLoading />
               | Failed(_error) => <div> (str_to_ele("error")) </div>
               | Loaded(result) =>
                 parse(result)##allSnippets
                 |> Array.map(snippet =>
                      switch snippet {
                      | None => <div> (str_to_ele("failed")) </div>
                      | Some(x) =>
                        <Card key=x##id>
                          <H3> (str_to_ele(x##title)) </H3>
                          <P> (str_to_ele(x##description)) </P>
                          <Code> (str_to_ele(x##content)) </Code>
                          <JsSnippet id=x##id />
                        </Card>
                      }
                    )
                 |> ReasonReact.arrayToElement;
               }
           )
      </Query>
    </PageFrame>;
  }
};
