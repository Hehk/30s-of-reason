open Utils;

module SnippetQuery = [%graphql
  {|
  query getAllSnippets($filter: String!) {
    allSnippets(query: $filter) {
      content,
      title,
      description,
      id,
      section
    }
  }
|}
];

module Query = Apollo.Client.Query;

let rec createSections = (~sections=[], snippets) =>
  switch snippets {
  | [] => List.rev(sections)
  | [hd, ..._] =>
    let (newSection, tl) =
      List.partition(x => x##section === hd##section, snippets);
    createSections(tl, ~sections=[newSection, ...sections]);
  };

let rec filterOutVariant = (acc, l) =>
  switch l {
  | [] => List.rev(acc)
  | [hd, ...tl] =>
    switch hd {
    | None => filterOutVariant(acc, tl)
    | Some(x) => filterOutVariant([x, ...acc], tl)
    }
  };

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
                 |> Array.to_list
                 |> filterOutVariant([])
                 |> createSections
                 |> List.map(
                      fun
                      | [] => []
                      | [hd, ..._] as section => {
                          let sectionName = hd##section;
                          [
                            <Divider key=("divider-" ++ sectionName) />,
                            ele_of_str(sectionName),
                            ...section
                               |> List.map(x =>
                                    <SnippetItem
                                      key=x##id
                                      id=x##id
                                      title=x##title
                                      description=x##description
                                      content=x##content
                                    />
                                  )
                          ];
                        }
                    )
                 |> List.flatten
                 |> ele_of_list
               }
           )
      </Query>
    </PageFrame>;
  }
};
