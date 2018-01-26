module GraphQL = {
  let types = Snippet.graphQLType;
  let query = "type Query { allSnippets(query: String): [Snippet]!}";
  let make = () => {
    let snippet = Snippet.Handler.make();
    let resolvers = {"Query": Js.Obj.empty() |> Js.Obj.assign(snippet.queries)};
    GraphQLTools.makeExecutableSchema({"typeDefs": types ++ query, "resolvers": resolvers})
    |> ApolloServerExpress.createGraphQLExpressMiddleware
  };
};
