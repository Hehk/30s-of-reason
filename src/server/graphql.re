let schema =  {
  let types = Snippet.graphQLType;
  let query = {|
    type Query {
      allSnippets(query: String): [Snippet]!
      snippet(id: ID!): Snippet!
    }
  |};
  let snippet = Snippet.Handler.make();
  let resolvers = {"Query": Js.Obj.empty() |> Js.Obj.assign(snippet.queries)};

  {"typeDefs": types ++ query, "resolvers": resolvers};
};

