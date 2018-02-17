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

let rec createSections = (~sections=[], snippets) =>
  switch snippets {
  | [] => List.rev(sections)
  | [hd, ..._] =>
    let (newSection, tl) = List.partition(x => x##section === hd##section, snippets);
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

let renderSections = (query, snippets) =>
  snippets
  |> List.map(
       fun
       | [] => []
       | [hd, ..._] as section => {
           let sectionName = hd##section;
           [
             <H2 key=("section-" ++ sectionName)> (ele_of_str(sectionName)) </H2>,
             ...section
                |> List.map(x =>
                     <SnippetItem
                       key=x##id
                       id=x##id
                       title=x##title
                       description=x##description
                       content=x##content
                       query
                     />
                   )
           ];
         }
     )
  |> List.flatten;

let component = ReasonReact.statelessComponent("snippets");

let renderLoading = () =>
  [
    <H2> (ele_of_str("Loading")) </H2>,
    <SnippetItem.Loading />,
    <SnippetItem.Loading />
  ]
  |> ele_of_list;

let renderFailed = () => ele_of_str("error");

let renderLoaded = (~query, snippets) =>
  snippets
  |> Array.to_list
  |> filterOutVariant([])
  |> createSections
  |> renderSections(query)
  |> ele_of_list;

let make = (~query, ~filter="", _children) => {
  ...component,
  render: _self => {
    module Query = (val (query: (module Apollo.Query)));
    let snippetQuery = SnippetQuery.make(~filter, ());
    <PageFrame>
      <Query query=snippetQuery>
        ...(
             (response, parse) =>
               switch response {
               | Loading => renderLoading()
               | Failed(_error) => renderFailed()
               | Loaded(result) => renderLoaded(~query, parse(result)##allSnippets)
               }
           )
      </Query>
    </PageFrame>;
  }
};
